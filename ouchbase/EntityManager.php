<?php

namespace Ouchbase;

use Ouchbase\Entity\Proxy;
use Ouchbase\Exception\EntityModifiedException;
use Ouchbase\Exception\EntityUpdateFailedException;

/**
 * @todo Register managed models instead of extending from EntityManager
 */
abstract class EntityManager
{
    /**
     * Override this property in subclasses
     * Instead of having annotations or external configuration
     * @var array
     */
    protected $entityRepositories = array();

    /**
     * @var UnitOfWork
     */
    private $uow;

    /**
     * @var IdentityMap
     */
    private $im;

    /**
     * @var \Couchbase
     */
    private $cb;

    /**
     * @var Repository[]
     */
    private $_repositories = array();

    /**
     * @param \Couchbase $couchbase
     */
    public function __construct(\Couchbase $couchbase)
    {
        $this->im = new IdentityMap();
        $this->uow = new UnitOfWork($this, $this->im);

        $this->cb = $couchbase;
        //$this->cb->setOption(COUCHBASE_OPT_SERIALIZER, COUCHBASE_SERIALIZER_JSON_ARRAY);
    }

    /**
     * @param string $entityClassName
     * @return Repository
     */
    public function getRepository($entityClassName)
    {
        if (is_object($entityClassName)) {
            $entityClassName = Helper::getEntityClass($entityClassName);
        }

        return $this->getCachedRepository($this->entityRepositories[$entityClassName]);
    }

    /**
     * @param string $repositoryClassName
     * @return Repository
     */
    protected function getCachedRepository($repositoryClassName)
    {
        if (!isset($this->_repositories[$repositoryClassName])) {
            $this->_repositories[$repositoryClassName] = new $repositoryClassName($this->uow, $this->im, $this->cb);
        }

        return $this->_repositories[$repositoryClassName];
    }

    /**
     * @param Entity $entity
     * @return $this
     */
    public function persist(Entity $entity/*, todo $ttl ??? */)
    {
        if ($this->im->contains($entity)) {
            $this->uow->persist($entity);
        }
        else {
            $this->im->register($entity, $this->getRepository(Helper::getEntityClass($entity))->getConverter()->toArray($entity));
            $this->uow->insert($entity);
        }

        return $this;
    }

    /**
     * @param Entity $entity
     * @return $this
     */
    public function delete(Entity $entity)
    {
        $this->uow->delete($entity);
        return $this;
    }

    /**
     * @param Entity $entity
     * @param bool $concurrent If entity may have concurrent updates
     * @throws \LogicException
     * @return $this
     */
    public function refresh(Entity $entity, $concurrent = false)
    {
        $this->getRepository(Helper::getEntityClass($entity))->refresh($entity, $concurrent);
        return $this;
    }

    /**
     * @return $this
     */
    public function flush()
    {
        $this->uow->commit();
        return $this;
    }

    /**
     * @return $this
     */
    public function clear()
    {
        $this->im->clear();
        $this->uow->clear();

        return $this;
    }

    /**
     * Swap / Apply callback to entity and save it "atomically"
     *
     * @param Entity $entity
     * @param callable $callback Accepts entity as argument and modifies it
     * @throws EntityUpdateFailedException
     * @return $this
     */
    public function update(Entity $entity, $callback/*, $arg1, $arg2 */)
    {
        if ($entity instanceof Proxy) {
            $entity = $entity->_getObject();
        }

        $updated = false;
        $attempts = 0;
        $args = func_get_args();
        unset($args[1]);
        do {
            ++$attempts;
            $this->refresh($entity, true);
            $result = call_user_func_array($callback, $args);

            try {
                $this->uow->commit($entity);
                $updated = true;
            }
            catch (EntityModifiedException $e) {
                usleep(mt_rand(20, 60)); // Lets not kill the db :)
            }
        } while (!$updated || $attempts > 20);

        if (!$updated) {
            throw new EntityUpdateFailedException(sprintf("Couldn't update entity in %d attempts", $attempts));
        }

        return $result;
    }

}