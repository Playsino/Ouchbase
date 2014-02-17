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
     * @var array
     */
    private _reflections;

    /**
     * @param \Ouchbase\UnitOfWork unitOfWork
     * @param \Ouchbase\IdentityMap identityMap
     * @param \Couchbase couchbase
     */
    public function __construct(<Ouchbase\UnitOfWork> unitOfWork, <Ouchbase\IdentityMap> identityMap, <Couchbase> couchbase)
    {
        let this->uow = unitOfWork;
        let this->im = identityMap;
        let this->cb = couchbase;
        let this->_reflections = [];
    }

    /**
     * @param int|string id
     * @param bool concurrent
     * @return \Ouchbase\Entity|null
     */
    public function find(id, boolean concurrent = false) -> <Ouchbase\Entity>
    {
        var entity;
        let entity = this->im->getEntity(this->className, id);
        if entity {
            return entity;
        }

        var cas, data, dataWithCas;
        let dataWithCas = this->executeWithoutTimeouts([self, "__getWithCas"], entity->getId());
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
    public function refresh(<Ouchbase\Entity> entity, boolean concurrent = false) -> <Ouchbase\Repository>
    {
        if !this->im->contains(entity) {
            throw new \Ouchbase\Exception\EntityLogicException(entity, "was not persisted");
        }

        if entity instanceof Ouchbase\EntityProxy {
            let entity = entity->_getObject();
        }

        // todo Remove code duplication with find
        var cas, data, dataWithCas;
        let dataWithCas = this->executeWithoutTimeouts([self, "__getWithCas"], entity->getId());
        let data = dataWithCas["data"],
            cas = dataWithCas["cas"];

        if !data {
            // todo Throw exception here?
            return null;
        }

        if !is_array(data) {
            let data = json_decode(data, true);
        }

        var refreshed;
        let refreshed = this->toObject(data);

        // The following code could be moved into updateExistingEntity method
        this->im->updateOriginalData(entity, data);

        for property in this->getClassReflection()->getProperties() {
            let property = this->getPropertyReflection(property->getName());
            property->setValue(entity, property->getValue(refreshed));
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
        var entity, entities, cas, data, dataWithCas;
        let entities = [];

        var cas, data, dataWithCas;
        let dataWithCas = this->executeWithoutTimeouts([self, "__getMultiWithCas"], ids);
        let data = dataWithCas["data"],
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
    public function insert(<Ouchbase\Entity> entity) -> <Ouchbase\Repository>
    {
        var data;
        let data = this->toArray(entity);
        this->executeWithoutTimeouts("set", self::getKey(entity->getId()), json_encode(data));
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
    public function update(entity, cas) -> <Ouchbase\Repository>
    {
        // todo Diff calculation is responsibility of unit of work
        if entity instanceof Ouchbase\EntityProxy {
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
            this->executeWithoutTimeouts("replace", self::getKey(entity->getId()), json_encode(data));
            return this;
        }

        if !this->executeWithoutTimeouts("replace", self::getKey(entity->getId()), json_encode(data), 0, cas) {
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
    public function delete(<Ouchbase\Entity> entity, cas) -> <Ouchbase\Repository>
    {
        if !cas {
            this->executeWithoutTimeouts("delete", self::getKey(entity->getId()));
        }
        else {
            // todo Figure out how to be with try/catch block
            try {
                this->executeWithoutTimeouts("delete", self::getKey(entity->getId()), cas);
            }
            catch (\CouchbaseKeyMutatedException e) {
                var e;
                let e = new \Ouchbase\Exception\EntityModifiedException(entity, "was modified");
                e->setAction(\Ouchbase\Exception\EntityModifiedException::ACTION_DELETE);

                throw e;
            }
        }

        this->im->unregister(entity);

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
     * @param callable|string command Couchbase command or callback that takes Couchbase instance as an argument or
     * @throws \CouchbaseLibcouchbaseException
     * @return mixed
     */
    private function executeWithoutTimeouts(command)
    {
        int attempts = 0;
        while attempts < 3 {
            try {
                if is_string(command) {
                    return call_user_func_array(array(this->cb, command), array_slice(func_get_args(), 1));
                }

                return command(this->cb);
            }
            catch (\CouchbaseLibcouchbaseException e) { let ++attempts; }
        }

        throw e;
    }

    /**
     * @param int|string id
     * @return string
     */
    private static function getKey(id) -> string
    {
        return this->keyPrefix . id;
    }

    /**
     * @return \ReflectionClass
     */
    private function getClassReflection() -> <ReflectionClass>
    {
        if !isset this->_reflections[this->className] {
            var reflection;
            let reflection = new \ReflectionClass(this->className);
            let this->_reflections[this->className] = [
                "class": reflection,
                "properties": [],
            ];
        }

        return this->_reflections[this->className]["class"];
    }

    /**
     * @param string property
     * @return \ReflectionProperty
     */
    private function getPropertyReflection(property) -> <ReflectionProperty>
    {
        if !isset this->_reflections[this->className]["properties"][property] {
            var reflection;
            let reflection = this->getClassReflection(this->className)->getProperty(property);
            reflection->setAccessible(true);
            this->_reflections[this->className]["properties"][property] = reflection;
        }

        return this->_reflections[this->className]["properties"][property];
    }

    /**
     * @param int|string id
     * @return array [value, cas]
     */
    public function __getWithCas(id)
    {
        var cas, data;
        let data = this->cb->get(self::getKey(id), null, cas);

        return ["data": data, "cas": cas];
    }

    /**
     * @param array ids
     * @return array [value, cas]
     */
    public function __getMultiWithCas(ids)
    {
        var idsToKeys, keysToCas, cas, data;
        let idsToKeys = [],
            keysToCas = [],
            cas = [];

        foreach (ids as id) {
            let idsToKeys[id] = self::getKey(id);
        }

        let data = this->cb->getMulti(idsToKeys, keysToCas);

        foreach (ids as id) {
            let cas[id] = keysToCas[idsToKeys[id]];
        }

        return ["data": data, "cas": cas];
    }

    abstract public function toArray(<Ouchbase\Entity> $entity) -> [];

    abstract public function toObject($data) -> <Ouchbase\Entity>;

}