<?php

namespace Ouchbase;

/**
 * Provides an interface that all Ouchbase entities have to implement
 */
interface Entity
{
    /**
     * @return int|string
     */
    public function getId();

}

/**
 * The EntityManager is the central access point to Ouchbase functionality.
 *
 * It is a facade to all different OKVM subsystems such as UnitOfWork,
 * IdentityMap and Repository API.
 */
class EntityManager
{
    /**
     * Creates a new EntityManager that operates on the given Couchbase connection
     *
     * @param \Couchbase $couchbase
     */
    public function __construct(\Couchbase $couchbase) {}

    /**
     * Registers repository class for the given entity class name
     *
     * @param string $entityClassName
     * @param string $entityRepositoryClassName
     * @return $this
     */
    public function registerManagedEntityClass($entityClassName, $entityRepositoryClassName) {}

    /**
     * Registers repository classes for the given entity class names
     *
     * @param array $map (entity class name => entity repository class name)
     * @return $this
     */
    public function registerManagedEntityClasses(array $map) {}

    /**
     * Returns repository for the given entity or by the given class name
     *
     * If repository wasn't registered then Exception\EntityManagerException
     * exception will be thrown
     *
     * @param string|Entity $entityClassName
     * @return Repository
     * @throws Exception\EntityManagerException
     */
    public function getRepository($entityClassName) {}

    /**
     * Tells the EntityManager to make an instance managed and persistent.
     *
     * The entity will be stored into the database after the flush operation.
     *
     * If the entity was previously marked for deletion then
     * Exception\EntityLogicException exception will be thrown
     *
     * @param Entity $entity
     * @return $this
     * @throws Exception\EntityLogicException
     */
    public function persist($entity) {}

    /**
     * Tells the EntityManager to delete an entity instance.
     *
     * The entity will be deleted from the database after the flush operation.
     *
     * If the entity wasn't persisted (managed) then Exception\EntityLogicException
     * exception will be thrown
     *
     * @param Entity $entity
     * @return $this
     * @throws Exception\EntityLogicException
     */
    public function delete(Entity $entity) {}

    /**
     * Refreshes the persistent state of an entity from the database,
     * overriding any local changes that have not yet been persisted.
     *
     * If the entity wasn't persisted (managed) then Exception\EntityLogicException
     * exception will be thrown
     *
     * @param Entity $entity
     * @param bool $concurrent Pass true to not override external changes in Couchbase
     * @return $this
     * @throws Exception\EntityLogicException
     */
    public function refresh(Entity $entity, $concurrent = false) {}

    /**
     * Flushes all changes to objects that have been queued up to now to the database.
     * This effectively synchronizes the in-memory state of managed objects with the
     * database.
     *
     * If any entity fetched in concurrent mode (with CAS) was updated then
     * EntityModifiedException exception will be thrown
     *
     * @return $this
     * @throws Exception\EntityModifiedException
     */
    public function flush() {}

    /**
     * Clears the EntityManager. All entities that are currently managed
     * by this EntityManager become detached.
     *
     * @return $this
     */
    public function clear() {}

    /**
     * Swap / Applied the callback to the entity and saves it "atomically"
     *
     * Throws Exception\EntityUpdateFailedException if update fails
     *
     * @param Entity $entity
     * @param callable $callback Accepts entity as an argument and modifies it
     * @return $this
     * @throws Exception\EntityUpdateFailedException
     */
    public function update(Entity $entity, $callback) {}

    /**
     * Returns used Couchbase connection
     *
     * @return \Couchbase
     */
    public function getConnection() {}

}

/**
 * Proxy needed for lazy fetching from Couchbase for composite Ouchbase entities
 * that have other Ouchbase entities as their properties
 */
class EntityProxy implements Entity
{
    /**
     * Creates proxy object by callback which will be called when proxy is accessed
     * and optional entities id that will be used in getId() method
     *
     * @param callable $creator
     * @param int|string $id Optional
     * @return EntityProxy
     */
    public function __construct($creator, $id = null) {}

    /**
     * Returns proxied entity id
     *
     * @return int|string
     */
    public function getId() {}

    /**
     * Returns proxied entity
     *
     * Throws Exception\EntityLogicException exception if callbacks that creates
     * proxied entity fails
     *
     * @return Entity
     * @throws Exception\EntityLogicException
     */
    public function getEntity() {}

    /**
     * Tells if the entity is already proxied
     *
     * @return bool
     */
    public function isProxied() {}

}

/**
 * Utility class. Don't use it :)
 */
class _etc
{
    /**
     * Returns real entity class. Works for proxies.
     *
     * @param Entity $entity
     * @return string
     */
    public static function getEntityClass($entity) {}

    /**
     * Returns unique entity hash
     *
     * @param string|Entity $className
     * @param int|string|null $id
     * @return string
     */
    public static function getEntityHash($className, $id = null) {}

}

/**
 * The IdentityMap stores entities to ensure that there is always
 * only one instance of each entity.
 *
 * It also stores original entity data fetched from Couchbase which
 * is used for rollbacks
 */
class IdentityMap
{
    /**
     * Registers entity in the map
     *
     * @param Entity $entity
     * @param array $data Original entity data
     * @return $this
     * @throws Exception\EntityLogicException if entity is already registered
     */
    public function register(Entity $entity, array $data) {}

    /**
     * Unregisters entity from the map
     * 
     * @param Entity $entity
     * @return $this
     * @throws Exception\EntityLogicException if entity wasn't registered
     */
    public function unregister(Entity $entity) {}

    /**
     * Returns entity by class name and id
     * 
     * @param string $className
     * @param int|string $id
     * @return Entity|null
     */
    public function getEntity($className, $id) {}

    /**
     * Tells if entity is registered in the map
     * 
     * @param Entity entity
     * @return bool
     */
    public function contains(Entity $entity) {}

    /**
     * Returns original entity data
     * 
     * @param Entity entity
     * @return array|null
     */
    public function getOriginalData(Entity $entity) {}

    /**
     * Updates original entity data
     *
     * @param Entity entity
     * @param array $data
     * @return $this
     */
    public function updateOriginalData(Entity $entity, array $data) {}

    /**
     * Unregisters all registered entities
     *
     * @return $this
     */
    public function clear() {}

}

/**
 * Implements Couchbase interaction operations
 */
class Repository
{
    /**
     * Prefix which is used for entity keys in Couchbase
     *
     * Override this property in subclasses
     * @var string
     */
    protected $keyPrefix = '';

    /**
     * Entity class name
     *
     * Override this property in subclasses
     * @var string
     */
    protected $className;

    /**
     * @param UnitOfWork $unitOfWork
     * @param IdentityMap $identityMap
     * @param \Couchbase $couchbase
     */
    public function __construct(UnitOfWork $unitOfWork, IdentityMap $identityMap, \Couchbase $couchbase) {}

    /**
     * Finds an object by its primary key / identifier.
     *
     * @param int|string $id
     * @param bool $concurrent Pass true to not override external changes in Couchbase
     * @return Entity|null
     */
    public function find($id, $concurrent = false) {}

    /**
     * Refreshes the persistent state of an entity from the database,
     * overriding any local changes that have not yet been persisted.
     *
     * If the entity wasn't persisted (managed) then Exception\EntityLogicException
     * exception will be thrown
     *
     * @param Entity $entity
     * @param bool $concurrent Pass true to not override external changes in Couchbase
     * @return $this
     * @throws Exception\EntityLogicException
     */
    public function refresh(Entity $entity, $concurrent = false) {}

    /**
     * Finds all objects in the repository.
     *
     * @param array $ids
     * @param bool $concurrent Pass true to not override external changes in Couchbase
     * @return Entity[]
     */
    public function findAll(array $ids, $concurrent = false) {}

    /**
     * Inserts (stores) entity to Couchbase.
     *
     * Do not use this method if you don't understand how Ouchbase works. This method
     * will be called during flush operation.
     *
     * @param Entity $entity
     * @return $this
     */
    public function insert(Entity $entity) {}

    /**
     * Updates entity in Couchbase
     *
     * Do not use this method if you don't understand how Ouchbase works. This method
     * will be called during flush operation.
     *
     * @param Entity $entity
     * @param string|null $cas
     * @return $this
     * @throws Exception\EntityModifiedException
     * @throws Exception\EntityLogicException
     */
    public function update(Entity $entity, $cas = null) {}

    /**
     * Deletes entity from Couchbase
     *
     * Do not use this method if you don't understand how Ouchbase works. This method
     * will be called during flush operation.
     *
     * @param Entity $entity
     * @param string|null $cas
     * @return $this
     * @throws Exception\EntityModifiedException
     */
    public function delete(Entity $entity, $cas = null) {}

    /**
     * Returns entity Couchbase key
     *
     * @param int|string $id
     * @return string
     */
    public static function getKey($id) {}

    /**
     * Converts array data to Entity object
     *
     * Please override this method in custom repositories
     *
     * @param array $data
     * @return Entity
     */
    public function toObject($data) {}

    /**
     * Converts Entity object to array data
     *
     * Please override this method in custom repositories
     *
     * @param Entity $entity
     * @return array|string
     */
    public function toArray(Entity $entity) {}

}

/**
 * The UnitOfWork is responsible for tracking changes to objects during an
 * "object-level" transaction and for writing out changes to the database
 * in the correct order.
 */
class UnitOfWork
{
    /**
     * Initializes a new UnitOfWork instance, bound to the given EntityManager and IdentityMap
     *
     * @param EntityManager $entityManager
     * @param IdentityMap $identityMap
     */
    public function __construct(EntityManager $entityManager, IdentityMap $identityMap) {}

    /**
     * Persists an entity as part of the current unit of work.
     *
     * @param Entity $entity
     * @param string|null $cas
     * @return $this
     * @throws Exception\EntityLogicException
     */
    public function persist(Entity $entity, $cas = null) {}

    /**
     * Deletes an entity as part of the current unit of work.
     *
     * @param Entity $entity
     * @return $this
     * @throws Exception\EntityLogicException
     */
    public function delete(Entity $entity) {}

    /**
     * Inserts an entity as part of the current unit of work.
     *
     * @param Entity $entity
     * @return $this
     */
    public function insert(Entity $entity) {}

    /**
     * Commits all changes to Couchbase
     *
     * @param Entity|null $entity If entity is not managed no exception will be thrown
     * @throws Exception\EntityModifiedException
     */
    public function commit(Entity $entity = null) {}

    /**
     * Forget about all previously set entity operations
     *
     * @return $this
     */
    public function clear() {}

}

namespace Ouchbase\Exception;

class EntityManagerException extends \LogicException {}

class EntityLogicException extends \LogicException {}

/**
 * Is thrown during flush operation in case if any entity fetched
 * in concurrent mode (with CAS) was modified externally.
 */
class EntityModifiedException extends EntityLogicException
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

class EntityUpdateFailedException extends \RuntimeException {}
