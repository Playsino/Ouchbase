namespace Ouchbase;

class UnitOfWork
{
    /**
     * @var \Ouchbase\IdentityMap
     */
    private im;

    /**
     * @var \Ouchbase\EntityManager
     */
    private em;

    /**
     * @var \Ouchbase\Entity[]
     */
    private persisted = [];

    /**
     * @var \Ouchbase\Entity[]
     */
    private inserted = [];

    /**
     * @var \Ouchbase\Entity[]
     */
    private deleted = [];

    /**
     * @param \Ouchbase\EntityManager entityManager
     * @param \Ouchbase\IdentityMap identityMap
     */
    public function __construct(<\Ouchbase\EntityManager> entityManager, <\Ouchbase\IdentityMap> identityMap)
    {
        let this->em = entityManager;
        let this->im = identityMap;
    }

    /**
     * @param \Ouchbase\Entity entity
     * @param string|null cas
     * @throws \Ouchbase\Exception\EntityLogicException
     * @return this
     */
    public function persist(<\Ouchbase\Entity> entity, cas = null) -> <\Ouchbase\UnitOfWork>
    {
        if isset this->deleted[\Ouchbase\_etc::getEntityHash(entity)] {
            throw new \Ouchbase\Exception\EntityLogicException(entity, "was marked as deleted");
        }

        let this->persisted[\Ouchbase\_etc::getEntityHash(entity)] = [entity, cas];

        return this;
    }

    /**
     * @param \Ouchbase\Entity entity
     * @throws \Ouchbase\Exception\EntityLogicException
     * @return this
     */
    public function delete(<\Ouchbase\Entity> entity) -> <\Ouchbase\UnitOfWork>
    {
        var hash;
        let hash = \Ouchbase\_etc::getEntityHash(entity);
        if !isset this->persisted[hash] {
            throw new \Ouchbase\Exception\EntityLogicException(entity, "was not persisted");
        }

        let this->deleted[hash] = this->persisted[hash];
        unset this->persisted[hash];

        return this;
    }

    /**
     * @param \Ouchbase\Entity entity
     * @return this
     */
    public function insert(<\Ouchbase\Entity> entity) -> <\Ouchbase\UnitOfWork>
    {
        let this->inserted[\Ouchbase\_etc::getEntityHash(entity)] = entity;
        return this;
    }

    /**
     * @param \Ouchbase\Entity|null entity If entity is not managed no exception will be thrown
     * @throws \Ouchbase\Exception\EntityModifiedException
     */
    public function commit(<\Ouchbase\Entity> entity = null) -> <\Ouchbase\UnitOfWork>
    {
        var e;
        try {
            // In case of rollback original data will be taken from im because
            // original data in this->im will be updated after each particular update
            var im;
            let im = clone this->im;

            this->commitUpdates(entity);
            this->commitDeletes(entity);
            // Inserts should go last because they don't throw \Ouchbase\Exception\EntityModifiedException
            // and also inserted entities become persisted after insert so don't want
            // them to be checked during commitUpdates
            this->commitInserts(entity);
            return this;
        }
        catch \Ouchbase\Exception\EntityModifiedException|Exception, e {
            // If we tried to update only one entity then no rollback is needed
            if null !== entity {
                throw e;
            }

            // Otherwise rollback all committed changes to keep logical consistency
            if e->getAction() === \Ouchbase\Exception\EntityModifiedException::ACTION_UPDATE {
                this->rollbackUpdates(im, e->getEntity());
            }
            else {
                if e->getAction() === \Ouchbase\Exception\EntityModifiedException::ACTION_DELETE {
                    this->rollbackUpdates(im);
                    this->rollbackDeletes(im, e->getEntity());
                }
            }

            // Clear entity manager because all logic that modified the entities should be
            // re-applied (new values should be re-read from the db and new calculations
            // should be applied)
            this->em->clear();
            throw e;
        }

        return this;
    }

    /**
     * @param \Ouchbase\Entity|null entity
     * @return this
     */
    private function commitInserts(<\Ouchbase\Entity> entity = null) -> <\Ouchbase\UnitOfWork>
    {
        if null !== entity {
            var hash;
            let hash = \Ouchbase\_etc::getEntityHash(entity);
            if hash && isset this->inserted[hash] {
                this->em->getRepository(entity)->insert(entity);
                unset this->inserted[hash];
            }

            return this;
        }

        for entity in this->inserted {
            this->em->getRepository(entity)->insert(entity);
        }

        let this->inserted = [];

        return this;
    }

    /**
     * @param \Ouchbase\Entity|null entity
     * @return this
     */
    private function commitDeletes(<\Ouchbase\Entity> entity = null) -> <\Ouchbase\UnitOfWork>
    {
        if null !== entity {
            var hash;
            let hash = \Ouchbase\_etc::getEntityHash(entity);
            if hash && isset this->deleted[hash] {
                this->em->getRepository(entity)->delete(entity, this->deleted[hash][1]);
                unset this->deleted[hash];
            }

            return this;
        }

        var data;
        for data in this->deleted {
            this->em->getRepository(data[0])->delete(data[0], data[1]);
        }

        let this->deleted = [];

        return this;
    }

    /**
     * @param \Ouchbase\Entity|null entity
     * @return this
     */
    private function commitUpdates(<\Ouchbase\Entity> entity = null) -> <\Ouchbase\UnitOfWork>
    {
        if null !== entity {
            var hash;
            let hash = \Ouchbase\_etc::getEntityHash(entity);
            if hash && isset this->persisted[hash] {
                this->em->getRepository(entity)->update(entity, this->persisted[hash][1]);
            }

            return this;
        }

        var data;
        for data in this->persisted {
            this->em->getRepository(data[0])->update(data[0], data[1]);
        }

        return this;
    }

    /**
     * @param IdentityMap im
     * @param \Ouchbase\Entity entity
     * @return this
     */
    private function rollbackUpdates(<\Ouchbase\IdentityMap> im, <\Ouchbase\Entity> entity = null) -> <\Ouchbase\UnitOfWork>
    {
        var repository, hash = null, data;
        if null !== entity {
            let hash = \Ouchbase\_etc::getEntityHash(entity); 
        }

        for data in this->persisted  {
            if hash && \Ouchbase\_etc::getEntityHash(data[0]) === hash {
                break;
            }

            let repository = this->em->getRepository(data[0]);
            this->em->getConnection()->replace(repository->getKey(data[0]->getId()), im->getOriginalData(data[0]));
        }

        return this;
    }

    /**
     * @param IdentityMap im
     * @param \Ouchbase\Entity entity
     * @return this
     */
    private function rollbackDeletes(<\Ouchbase\IdentityMap> im, <\Ouchbase\Entity> entity) -> <\Ouchbase\UnitOfWork>
    {
        var repository, hash = null, data;
        if null !== entity {
            let hash = \Ouchbase\_etc::getEntityHash(entity); 
        }

        for data in this->deleted {
            if hash && \Ouchbase\_etc::getEntityHash(data[0]) === hash {
                break;
            }

            let repository = this->em->getRepository(data[0]);
            this->em->getConnection()->set(repository->getKey(data[0]->getId()), im->getOriginalData(data[0]));
        }

        return this;
    }

    /**
     * @return this
     */
    public function clear() -> <\Ouchbase\UnitOfWork>
    {
        let this->persisted = [],
            this->deleted = [],
            this->inserted = [];

        return this;
    }

}