<?php

namespace Ouchbase;

interface Entity
{
    /**
     * @return int|string
     */
    public function getId();

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
     * @var \Ouchbase\Entity[]
     */
    private $entities;

    /**
     * @var array
     */
    private $originalData;

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
