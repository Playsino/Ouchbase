<?php

namespace Ouchbase;

use Ouchbase\Exception\EntityLogicException;
use Ouchbase\Exception\EntityModifiedException;

class UnitOfWork
{
    /**
     * @var IdentityMap
     */
    private $im;

    /**
     * @var EntityManager
     */
    private $em;

    /**
     * @var array
     */
    private $persisted = array();

    /**
     * @var Entity[]
     */
    private $inserted = array();

    /**
     * @var array
     */
    private $deleted = array();

    /**
     * @param EntityManager $entityManager
     * @param IdentityMap $identityMap
     */
    public function __construct(EntityManager $entityManager, IdentityMap $identityMap)
    {
        $this->em = $entityManager;
        $this->im = $identityMap;
    }

    /**
     * @param Entity $entity
     * @param string|null $cas
     * @throws EntityLogicException
     * @return $this
     */
    public function persist(Entity $entity, $cas = null)
    {
        if (isset($this->deleted[Helper::getEntityHash($entity)])) {
            throw new EntityLogicException($entity, 'was marked as deleted');
        }

        $this->persisted[Helper::getEntityHash($entity)] = array($entity, $cas);

        return $this;
    }

    /**
     * @param Entity $entity
     * @throws EntityLogicException
     * @return $this
     */
    public function delete(Entity $entity)
    {
        $hash = Helper::getEntityHash($entity);
        if (!isset($this->persisted[$hash])) {
            throw new EntityLogicException($entity, 'was not persisted');
        }

        $this->deleted[$hash] = $this->persisted[$hash];
        unset($this->persisted[$hash]);

        return $this;
    }

    /**
     * @param Entity $entity
     * @return $this
     */
    public function insert(Entity $entity)
    {
        $this->inserted[Helper::getEntityHash($entity)] = $entity;
        return $this;
    }

    /**
     * @param Entity|null $entity If entity is not managed no exception will be thrown
     * @throws EntityModifiedException
     */
    public function commit(Entity $entity = null)
    {
        try {
            // In case of rollback original data will be taken from $im because
            // original data in $this->im will be updated after each particular update
            $im = clone $this->im;

            $this->commitUpdates($entity);
            $this->commitDeletes($entity);
            // Inserts should go last because they don't throw EntityModifiedException
            // and also inserted entities become persisted after insert so don't want
            // them to be checked during commitUpdates
            $this->commitInserts($entity);
        }
        catch (EntityModifiedException $e) {
            // If we tried to update only one entity then no rollback is needed
            if (null !== $entity) {
                throw $e;
            }

            // Otherwise rollback all committed changes to keep logical consistency
            if ($e->getAction() === EntityModifiedException::ACTION_UPDATE) {
                $this->rollbackUpdates($im, $e->getEntity());
            }
            else if ($e->getAction() === EntityModifiedException::ACTION_DELETE) {
                $this->rollbackUpdates($im);
                $this->rollbackDeletes($im, $e->getEntity());
            }

            // Clear entity manager because all logic that modified the entities should be
            // re-applied (new values should be re-read from the db and new calculations
            // should be applied)
            $this->em->clear();

            throw $e;
        }
    }

    /**
     * @param Entity|null $entity
     * @return $this
     */
    private function commitInserts(Entity $entity = null)
    {
        if (null !== $entity && ($hash = Helper::getEntityHash($entity)) && isset($this->inserted[$hash])) {
            $this->em->getRepository($entity)->insert($entity);
            unset($this->inserted[$hash]);

            return $this;
        }

        foreach ($this->inserted as $entity) {
            $this->em->getRepository($entity)->insert($entity);
        }

        $this->inserted = array();

        return $this;
    }

    /**
     * @param Entity|null $entity
     * @return $this
     */
    private function commitDeletes(Entity $entity = null)
    {
        if (null !== $entity && ($hash = Helper::getEntityHash($entity)) && isset($this->deleted[$hash])) {
            $this->em->getRepository($entity)->delete($entity, $this->deleted[$hash][1]);
            unset($this->deleted[$hash]);

            return $this;
        }

        foreach ($this->deleted as $data) {
            $this->em->getRepository($data[0])->delete($data[0], $data[1]);
        }

        $this->deleted = array();

        return $this;
    }

    /**
     * @param Entity|null $entity
     * @return $this
     */
    private function commitUpdates(Entity $entity = null)
    {
        if (null !== $entity && ($hash = Helper::getEntityHash($entity)) && isset($this->persisted[$hash])) {
            $this->em->getRepository($entity)->update($entity, $this->persisted[$hash][1]);
            return $this;
        }

        foreach ($this->persisted as $data) {
            $this->em->getRepository($data[0])->update($data[0], $data[1]);
        }

        return $this;
    }

    /**
     * @param IdentityMap $im
     * @param Entity $entity
     * @return $this
     */
    private function rollbackUpdates(IdentityMap $im, Entity $entity = null)
    {
        $hash = $entity !== null ? Helper::getEntityHash($entity) : null;
        foreach ($this->persisted as $data) {
            if ($hash && Helper::getEntityHash($data[0]) === $hash) {
                break;
            }

            $repository = $this->em->getRepository($data[0]);
            $repository->replace($repository->getKey($data[0]->getId()), $im->getOriginalData($data[0]));
        }

        return $this;
    }

    /**
     * @param IdentityMap $im
     * @param Entity $entity
     * @return $this
     */
    private function rollbackDeletes(IdentityMap $im, Entity $entity)
    {
        $hash = $entity !== null ? Helper::getEntityHash($entity) : null;
        foreach ($this->deleted as $data) {
            if ($hash && Helper::getEntityHash($data[0]) === $hash) {
                break;
            }

            $repository = $this->em->getRepository($data[0]);
            $repository->set($repository->getKey($data[0]->getId()), $im->getOriginalData($data[0]));
        }

        return $this;
    }

    /**
     * @return $this
     */
    public function clear()
    {
        $this->persisted =
        $this->deleted =
        $this->inserted = array();

        return $this;
    }

}