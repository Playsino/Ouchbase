namespace Ouchbase;

class IdentityMap
{
    /**
     * @var \Ouchbase\Entity[]
     */
    private entities;

    /**
     * @var array
     */
    private originalData;

    public function __construct()
    {
        let this->entities = [],
            this->originalData = [];
    }

    /**
     * @param \Ouchbase\Entity entity
     * @param array data
     * @return this
     * @throws \Ouchbase\Exception\EntityLogicException
     */
    public function register(<Ouchbase\Entity> entity, data) -> <Ouchbase\IdentityMap>
    {
        var hash;
        let hash = Ouchbase\_etc::getEntityHash(entity);
        if isset this->entities[hash] {
            throw new EntityLogicException(entity, "is already registered in the identity map");
        }

        let this->entities[hash] = entity;
        let this->originalData[hash] = data;

        return this;
    }

    /**
     * @param \Ouchbase\Entity entity
     * @return this
     * @throws \Ouchbase\Exception\EntityLogicException
     */
    public function unregister(<Ouchbase\Entity> entity) -> <Ouchbase\IdentityMap>
    {
        var hash;
        let hash = Ouchbase\_etc::getEntityHash(entity);
        if !(isset this->entities[hash]) {
            throw new EntityLogicException(entity, "is not registered in the identity map");
        }

        array_splice(this->entities, array_search(hash, this->entities), 1);
        array_splice(this->originalData, array_search(hash, this->originalData), 1);

        return this;
    }

    /**
     * @param \Ouchbase\Entity entity
     * @return bool
     */
    public function contains(<Ouchbase\Entity> entity) -> boolean
    {
        return isset this->entities[Ouchbase\_etc::getEntityHash(entity)];
    }

    /**
     * @param string className
     * @param int|string id
     * @return \Ouchbase\Entity|null
     */
    public function getEntity(string className, id)
    {
        var entity;
        if fetch entity, this->entities[Ouchbase\_etc::getEntityHash(className, id)] {
            return entity;
        }

        return null;
    }

    /**
     * @param \Ouchbase\Entity entity
     * @return array|null
     */
    public function getOriginalData(<Ouchbase\Entity> entity)
    {
        var data;
        if fetch data, this->originalData[Ouchbase\_etc::getEntityHash(entity)] {
            return data;
        }

        return null;
    }

    /**
     * @param \Ouchbase\Entity entity
     * @param array data
     * @return this
     */
    public function updateOriginalData(<Ouchbase\Entity> entity, data) -> <Ouchbase\IdentityMap>
    {
        let this->originalData[Ouchbase\_etc::getEntityHash(entity)] = data;
        return this;
    }

    /**
     * @return this
     */
    public function clear() -> <Ouchbase\IdentityMap>
    {
        let this->entities = [],
            this->originalData = [];
        return this;
    }

}
