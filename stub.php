<?php

namespace Ouchbase;

interface Entity
{
    /**
     * @return int|string
     */
    public function getId();

}

class EntityManager
{
    /**
     * @param string $entityClassName
     * @param string $entityRepositoryClassName
     * @return $this
     */
    public function registerManagedEntityClass($entityClassName, $entityRepositoryClassName) {}

    /**
     * @param array $map (entity class name => entity repository class name)
     * @return $this
     */
    public function registerManagedEntityClasses(array $map) {}

    /**
     * @param string $entityClassName
     * @return Repository
     */
    public function getRepository($entityClassName) {}

    /**
     * @param Entity $entity
     * @return $this
     */
    public function persist($entity/*, todo $ttl ??? */) {}

    /**
     * @param Entity $entity
     * @return $this
     */
    public function delete(Entity $entity) {}

    /**
     * @param Entity $entity
     * @param bool $concurrent If entity may have concurrent updates
     * @throws \LogicException
     * @return $this
     */
    public function refresh(Entity $entity, $concurrent = false) {}

    /**
     * @return $this
     */
    public function flush() {}

    /**
     * @return $this
     */
    public function clear() {}

    /**
     * Swap / Apply callback to entity and save it "atomically"
     *
     * @param Entity $entity
     * @param callable $callback Accepts entity as argument and modifies it
     * @throws \Ouchbase\Exception\EntityUpdateFailedException
     * @return $this
     */
    public function update(Entity $entity, $callback/*, $arg1, $arg2 */) {}

}

class EntityProxy implements Entity
{
    /**
     * @param callable $creator
     * @param int|string $id
     * @return \Ouchbase\EntityProxy
     */
    public function __construct($creator, $id = null) {}

    /**
     * @return int|string
     */
    public function getId() {}

    /**
     * @throws \Exception
     * @return Entity
     */
    public function getEntity() {}

    /**
     * @return bool
     */
    public function isProxied() {}

}

class _etc
{
    /**
     * @param Entity $entity
     * @return string
     */
    public static function getEntityClass($entity) {}

    /**
     * @param string|Entity $className
     * @param int|string|null $id
     * @return string
     */
    public static function getEntityHash($className, $id = null) {}

}

class IdentityMap
{
    /**
     * @param \Ouchbase\Entity $entity
     * @param array $data
     * @return $this
     * @throws \Ouchbase\Exception\EntityLogicException
     */
    public function register(\Ouchbase\Entity $entity, array $data) {}

    /**
     * @param \Ouchbase\Entity $entity
     * @return $this
     * @throws \Ouchbase\Exception\EntityLogicException
     */
    public function unregister(\Ouchbase\Entity $entity) {}

    /**
     * @param string $className
     * @param int|string $id
     * @return \Ouchbase\Entity|null
     */
    public function getEntity($className, $id) {}

    /**
     * @param \Ouchbase\Entity entity
     * @return bool
     */
    public function contains(\Ouchbase\Entity $entity) {}

    /**
     * @param \Ouchbase\Entity entity
     * @return array|null
     */
    public function getOriginalData(\Ouchbase\Entity $entity) {}

    /**
     * @param \Ouchbase\Entity entity
     * @param array $data
     * @return $this
     */
    public function updateOriginalData(\Ouchbase\Entity $entity, array $data) {}

    /**
     * @return $this
     */
    public function clear() {}

}

class Repository
{
    /**
     * Override this property in subclasses
     * @var string
     */
    public static $keyPrefix = '';

    /**
     * @param UnitOfWork $unitOfWork
     * @param IdentityMap $identityMap
     * @param \Couchbase $couchbase
     */
    public function __construct(UnitOfWork $unitOfWork, IdentityMap $identityMap, \Couchbase $couchbase) {}

    /**
     * @param int|string $id
     * @param bool $concurrent
     * @return Entity|null
     */
    public function find($id, $concurrent = false) {}

    /**
     * @param Entity $entity
     * @param bool $concurrent If entity may have concurrent updates
     * @throws \Ouchbase\Exception\EntityLogicException
     * @return $this
     */
    public function refresh(Entity $entity, $concurrent = false) {}

    /**
     * @param array $ids
     * @param bool $concurrent Only for entities fetched in this query
     * @return Entity[]
     */
    public function findAll(array $ids, $concurrent = false) {}

    /**
     * @param Entity $entity
     * @return $this
     */
    public function insert(Entity $entity) {}

    /**
     * @param Entity $entity
     * @param string |null$cas
     * @throws \Ouchbase\Exception\EntityModifiedException
     * @throws \Ouchbase\Exception\EntityLogicException
     * @param string|null $cas
     * @return $this
     */
    public function update(Entity $entity, $cas) {}

    /**
     * @param Entity $entity
     * @param string|null $cas
     * @throws \Ouchbase\Exception\EntityModifiedException
     * @return $this
     */
    public function delete(Entity $entity, $cas) {}

    /**
     * @param int|string $id
     * @return string
     */
    public static function getKey($id) {}

    /**
     * @param array $data
     * @return Entity
     */
    public function toObject($data) {}

    /**
     * @param Entity $entity
     * @return array|string
     */
    public function toArray(Entity $entity) {}

}

class UnitOfWork
{
    /**
     * @param EntityManager $entityManager
     * @param IdentityMap $identityMap
     */
    public function __construct(EntityManager $entityManager, IdentityMap $identityMap) {}
    /**
     * @param Entity $entity
     * @param string|null $cas
     * @throws \Ouchbase\Exception\EntityLogicException
     * @return $this
     */
    public function persist(Entity $entity, $cas = null) {}

    /**
     * @param Entity $entity
     * @throws \Ouchbase\Exception\EntityLogicException
     * @return $this
     */
    public function delete(Entity $entity) {}

    /**
     * @param Entity $entity
     * @return $this
     */
    public function insert(Entity $entity) {}

    /**
     * @param Entity|null $entity If entity is not managed no exception will be thrown
     * @throws \Ouchbase\Exception\EntityModifiedException
     */
    public function commit(Entity $entity = null) {}

    /**
     * @return $this
     */
    public function clear() {}

}

namespace Ouchbase\Exception;

class EntityLogicException extends \Exception {}

class EntityModifiedException extends \Ouchbase\Exception\EntityLogicException
{
    const ACTION_INSERT = 'insert';
    const ACTION_DELETE = 'delete';
    const ACTION_UPDATE = 'update';

    public function getAction() {}

    /**
     * Insert, delete or update
     * @param string $action
     * @return $this
     */
    public function setAction($action) {}

    /**
     * @return \Ouchbase\Entity
     */
    public function getEntity() {}

}

class EntityUpdateFailedException extends \Exception {}
