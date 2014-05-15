namespace Ouchbase;

class EntityManager
{
    /**
     * @var array
     */
    protected entityRepositories = [];

    /**
     * @var \Ouchbase\UnitOfWork
     */
    protected uow;

    /**
     * @var \Ouchbase\IdentityMap
     */
    protected im;

    /**
     * @var \Couchbase
     */
    protected cb;

    /**
     * @var \Ouchbase\Repository[]
     */
    protected _repositories = [];

    /**
     * @param \Couchbase couchbase
     */
    public function __construct(<\Couchbase> couchbase)
    {
        let this->im = new IdentityMap();
        let this->uow = new UnitOfWork(this, this->im);

        let this->cb = couchbase;
        //this->cb->setOption(COUCHBASE_OPT_SERIALIZER, COUCHBASE_SERIALIZER_JSON_ARRAY);
    }

    /**
     * @param string entityClassName
     * @param string entityRepositoryClassName
     * @return this
     */
    public function registerManagedEntityClass(string entityClassName, string entityRepositoryClassName) -> <\Ouchbase\EntityManager>
    {
        let this->entityRepositories[entityClassName] = entityRepositoryClassName;
        return this;
    }

    /**
     * @param array map (entity class name => entity repository class name)
     * @return this
     */
    public function registerManagedEntityClasses(map) -> <\Ouchbase\EntityManager>
    {
        var entityClassName, entityRepositoryClassName;
        for entityClassName, entityRepositoryClassName in map {
            let this->entityRepositories[entityClassName] = entityRepositoryClassName;
        }

        return this;
    }
    
    /**
     * @param string|\Ouchbase\Entity entityClassName
     * @return \Ouchbase\Repository
     */
    public function getRepository(entityClassName) -> <\Ouchbase\Repository>
    {
        if is_object(entityClassName) {
            let entityClassName = \Ouchbase\_etc::getEntityClass(entityClassName);
        }

        return this->getCachedRepository(this->entityRepositories[entityClassName]);
    }

    /**
     * @param string repositoryClassName
     * @return \Ouchbase\Repository
     */
    protected function getCachedRepository(string repositoryClassName) -> <\Ouchbase\Repository>
    {
        if !(isset this->_repositories[repositoryClassName]) {
            let this->_repositories[repositoryClassName] = new {repositoryClassName}(this->uow, this->im, this->cb);
        }

        return this->_repositories[repositoryClassName];
    }

    /**
     * @param \Ouchbase\Entity entity
     * @return this
     */
    public function persist(<\Ouchbase\Entity> entity) -> <\Ouchbase\EntityManager>
    {
        if this->im->contains(entity) {
            this->uow->persist(entity);
        }
        else {
            this->im->register(entity, this->getRepository(\Ouchbase\_etc::getEntityClass(entity))->toArray(entity));
            this->uow->insert(entity);
        }

        return this;
    }

    /**
     * @param \Ouchbase\Entity entity
     * @return this
     */
    public function delete(<\Ouchbase\Entity> entity) -> <\Ouchbase\EntityManager>
    {
        this->uow->delete(entity);
        return this;
    }

    /**
     * @param \Ouchbase\Entity entity
     * @param bool concurrent If entity may have concurrent updates
     * @throws \LogicException
     * @return this
     */
    public function refresh(<\Ouchbase\Entity> entity, bool concurrent = false) -> <\Ouchbase\EntityManager>
    {
        this->getRepository(\Ouchbase\_etc::getEntityClass(entity))->refresh(entity, concurrent);
        return this;
    }

    /**
     * @return this
     */
    public function flush() -> <\Ouchbase\EntityManager>
    {
        this->uow->commit();
        return this;
    }

    /**
     * @return this
     */
    public function clear() -> <\Ouchbase\EntityManager>
    {
        this->im->clear();
        this->uow->clear();

        return this;
    }

    /**
     * Swap / Apply callback to entity and save it "atomically"
     *
     * @param \Ouchbase\Entity entity
     * @param callable callback Accepts entity as argument and modifies it
     * @throws \Ouchbase\Exception\EntityUpdateFailedException
     * @return this
     */
    public function update(<\Ouchbase\Entity> entity, callback)
    {
        if entity instanceof \Ouchbase\EntityProxy {
            let entity = entity->_getObject();
        }

        var updated = false,
            attempts = 0,
            args, result, e;

        let args = func_get_args();
        unset args[1];

        loop {
            let attempts += 1;
            this->refresh(entity, true);
            let result = call_user_func_array(callback, args);

            try {
                this->uow->commit(entity);
                let updated = true;
            }
            catch \Ouchbase\Exception\EntityModifiedException, e {
                usleep(mt_rand(20, 60)); // Lets not kill the db :)
            }

            if updated || attempts > 20 {
                break;
            }
        }

        if !updated {
            throw new \Ouchbase\Exception\EntityUpdateFailedException(sprintf("Couldn't update entity in %d attempts", attempts));
        }

        return result;
    }

}