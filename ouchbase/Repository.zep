namespace Ouchbase;

abstract class Repository
{
    /**
     * Override this property in subclasses
     * @var string
     */
    protected keyPrefix = "";

    /**
     * Override this property in subclasses
     * @var string
     */
    protected className;

    /**
     * @var \Ouchbase\UnitOfWork
     */
    private uow;

    /**
     * @var \Ouchbase\IdentityMap
     */
    private im;

    /**
     * @var \Couchbase
     */
    protected cb;

    /**
     * @var \ReflectionClass
     */
    protected _classReflection;

    /**
     * @var \ReflectionProperty[]
     */
    protected _propertyReflections;

    /**
     * @param \Ouchbase\UnitOfWork unitOfWork
     * @param \Ouchbase\IdentityMap identityMap
     * @param \Couchbase couchbase
     */
    public function __construct(<\Ouchbase\UnitOfWork> unitOfWork, <\Ouchbase\IdentityMap> identityMap, <\Couchbase> couchbase)
    {
        let this->uow = unitOfWork;
        let this->im = identityMap;
        let this->cb = couchbase;
        let this->_propertyReflections = [];
    }

    /**
     * @param int|string id
     * @param bool concurrent
     * @return \Ouchbase\Entity|null
     */
    public function find(id, boolean concurrent = false) -> <\Ouchbase\Entity>|null
    {
        var entity;
        let entity = this->im->getEntity(this->className, id);
        if entity {
            return entity;
        }

        var cas, data, dataWithCas;
        let dataWithCas = this->executeWithoutTimeouts("__getWithCas", [id]);
        let data = dataWithCas["data"],
            cas = dataWithCas["cas"];

        if !data {
            return null;
        }

        if !is_array(data) {
            let data = json_decode(data, true);
        }

        let entity = this->toObject(data);
        this->im->register(entity, data);
        this->uow->persist(entity, concurrent ? cas : null);

        return entity;
    }

    /**
     * @param \Ouchbase\Entity entity
     * @param bool concurrent If entity may have concurrent updates
     * @throws \Ouchbase\Exception\EntityLogicException
     * @return this
     */
    public function refresh(<\Ouchbase\Entity> entity, boolean concurrent = false) -> <\Ouchbase\Repository>
    {
        if !this->im->contains(entity) {
            throw new \Ouchbase\Exception\EntityLogicException(entity, "was not persisted");
        }

        if entity instanceof \Ouchbase\EntityProxy {
            let entity = entity->_getObject();
        }

        // todo Remove code duplication with find
        var cas, data, dataWithCas;
        let dataWithCas = this->executeWithoutTimeouts("__getWithCas", [entity->getId()]);
        let data = dataWithCas["data"],
            cas = dataWithCas["cas"];

        if !data {
            // todo Throw exception here?
            return this;
        }

        if !is_array(data) {
            let data = json_decode(data, true);
        }

        var refreshed;
        let refreshed = this->toObject(data);

        // The following code could be moved into updateExistingEntity method
        this->im->updateOriginalData(entity, data);

        var property, propertyReflection;
        for property in  this->getClassReflection()->getProperties() {
            let propertyReflection = this->getPropertyReflection(property->getName());
            propertyReflection->setValue(entity, propertyReflection->getValue(refreshed));
        }

        if concurrent {
            this->uow->persist(entity, cas);
        }

        return this;
    }

    /**
     * @param array ids
     * @param bool concurrent Only for entities fetched in this query
     * @return \Ouchbase\Entity[]
     */
    public function findAll(ids, boolean concurrent = false)
    {
        var entity, entities, cas, data, dataWithCas, id, entityData;
        let entities = [],
            dataWithCas = this->executeWithoutTimeouts("__getMultiWithCas", [ids]),
            data = dataWithCas["data"],
            cas = dataWithCas["cas"];

        for id, entityData in data {
            let entity = this->im->getEntity(this->className, id);
            if entity {
                // todo Refresh here?
                let entities[] = entity;
                continue;
            }

            if !is_array(entityData) {
                let entityData = json_decode(entityData, true);
            }

            let entity = this->toObject(entityData);

            this->im->register(entity, entityData);
            this->uow->persist(entity, concurrent ? cas[id] : null);

            let entities[] = entity;
        }

        return entities;
    }

    /**
     * @param \Ouchbase\Entity entity
     * @return this
     */
    public function insert(<\Ouchbase\Entity> entity) -> <\Ouchbase\Repository>
    {
        var data;
        let data = this->toArray(entity);
        this->executeWithoutTimeouts("set", [this->getKey(entity->getId()), json_encode(data)]);
        this->uow->persist(entity);
        this->im->updateOriginalData(entity, data); // We register entity in IM in EM on persist

        return this;
    }

    /**
     * @todo cas argument is inconsistent here
     *
     * @param \Ouchbase\Entity entity
     * @param string|null cas
     * @throws \Ouchbase\Exception\EntityLogicException
     * @throws \Ouchbase\Exception\EntityModifiedException
     * @return this
     */
    public function update(<\Ouchbase\Entity> entity, cas = null) -> <\Ouchbase\Repository>
    {
        // todo Diff calculation is responsibility of unit of work
        if entity instanceof \Ouchbase\EntityProxy {
            if !entity->isProxied() {
                // Nothing changed
                return this;
            }

            let entity = entity->_getObject();
        }

        var data, originalData;
        let data = this->toArray(entity);
        let originalData = this->im->getOriginalData(entity);

        if !originalData {
            throw new \Ouchbase\Exception\EntityLogicException(entity, "was not registered in the identity map");
        }

        if data == originalData {
            // Nothing changed
            return this;
        }

        this->im->updateOriginalData(entity, data);

        if !cas {
            this->executeWithoutTimeouts("replace", [this->getKey(entity->getId()), json_encode(data)]);
            return this;
        }

        if !this->executeWithoutTimeouts("replace", [this->getKey(entity->getId()), json_encode(data), 0, cas]) {
            var e;
            let e = new \Ouchbase\Exception\EntityModifiedException(entity, "was modified");
            e->setAction(\Ouchbase\Exception\EntityModifiedException::ACTION_UPDATE);

            throw e;
        }

        return this;
    }

    /**
     * @todo cas argument is inconsistent here
     *
     * @param \Ouchbase\Entity entity
     * @param string|null cas
     * @throws \Ouchbase\Exception\EntityModifiedException
     * @return this
     */
    public function delete(<\Ouchbase\Entity> entity, cas = null) -> <\Ouchbase\Repository>
    {
        if !cas {
            this->executeWithoutTimeouts("delete", [this->getKey(entity->getId())]);
            this->im->unregister(entity);
            return this;
        }

        var e;
        try {
            this->executeWithoutTimeouts("delete", [this->getKey(entity->getId()), cas]);
            this->im->unregister(entity);
            return this;
        }
        catch \CouchbaseKeyMutatedException, e {
            var ex;
            let ex = new \Ouchbase\Exception\EntityModifiedException(entity, "was modified");
            ex->setAction(\Ouchbase\Exception\EntityModifiedException::ACTION_DELETE);
            throw ex;
        }

        return this;
    }

    /**
     * Executes the callback/Couchbase command that may throw Couchbase timeout
     * and ensures that the callback/Couchbase command is performed without timeouts
     * in the given number of attempts
     *
     * Optionally if Couchbase command was passed can take Couchbase command arguments
     *
     * Passing callback is needed for Couchbase commands that take arguments by reference
     *
     * @param callable|string command Couchbase or class method
     * @param array args Command args (optional)
     * @throws \CouchbaseLibcouchbaseException
     * @return mixed
     */
    protected function executeWithoutTimeouts(string method, array args = [])
    {
        var e;
        int attempts = 0;
        while attempts < 3 {
            try {
                if !(substr(method, 0, 2) == "__") { // hack :)
                    return call_user_func_array([this->cb, method], args);
                }
                return call_user_func_array([this, method], args);
            }
            catch \CouchbaseLibcouchbaseException, e {
                let attempts = attempts + 1;
            }
        }

        throw e;
    }

    /**
     * @param int|string id
     * @return string
     */
    public function getKey(id) -> string
    {
        return this->keyPrefix . id;
    }

    /**
     * @return \ReflectionClass
     */
    protected function getClassReflection() -> <\ReflectionClass>
    {
        if !this->_classReflection {
            let this->_classReflection = new \ReflectionClass(this->className);
        }

        return this->_classReflection;
    }

    /**
     * @param string property
     * @return \ReflectionProperty
     */
    protected function getPropertyReflection(string property) -> <\ReflectionProperty>
    {
        if !isset this->_propertyReflections[property] {
            var reflection;
            let reflection = this->getClassReflection()->getProperty(property);
            reflection->setAccessible(true);
            let this->_propertyReflections[property] = reflection;
        }

        return this->_propertyReflections[property];
    }

    /**
     * @param int|string id
     * @return array [value, cas]
     */
    public function __getWithCas(id)
    {
        var cas, data;
        let cas = null;
        let data = this->cb->get(this->getKey(id), null, cas);

        return ["data": data, "cas": cas];
    }

    /**
     * @param array ids
     * @return array [value, cas]
     */
    public function __getMultiWithCas(ids)
    {
        var idsToKeys, keysToCas, cas, data, id;
        let idsToKeys = [],
            keysToCas = [],
            cas = [];

        for id in ids {
            let idsToKeys[id] = this->getKey(id);
        }

        let data = this->cb->getMulti(idsToKeys, keysToCas);

        for id in ids {
            let cas[id] = keysToCas[idsToKeys[id]];
        }

        return ["data": data, "cas": cas];
    }

    abstract public function toArray(<\Ouchbase\Entity> entity) {}

    abstract public function toObject(data) -> <\Ouchbase\Entity> {}

}