<?php

namespace OuchbaseTest;

use Ouchbase\Entity;
use Ouchbase\EntityManager;
use Ouchbase\IdentityMap;
use Ouchbase\Repository;
use Ouchbase\UnitOfWork;

class TestEntity implements Entity
{
    /**
     * @var string
     */
    private $id;

    /**
     * @var mixed
     */
    public $property;

    /**
     * @param string $id
     * @param mixed $property
     */
    public function __construct($id, $property)
    {
        $this->id = $id;
        $this->property = $property;
    }

    /**
     * @return int|string
     */
    public function getId()
    {
        return $this->id;
    }

    /**
     * @return mixed
     */
    public function getProperty()
    {
        return $this->property;
    }

}

class TestEntityRepository extends Repository
{
    /**
     * @var string
     */
    public static $keyPrefix = 'test:';

    /**
     * @var string
     */
    protected static $className = 'OuchbaseTest\TestEntity';

    /**
     * @param array $data
     * @return Entity|TestEntity
     */
    public function toObject($data)
    {
        return new TestEntity($data['id'], $data['property']);
    }

    /**
     * @param Entity|TestEntity $entity
     * @return array|string
     */
    public function toArray($entity)
    {
        return array(
            'id' => $entity->getId(),
            'property' => $entity->getProperty(),
        );
    }

}

class IdentityMapMock extends IdentityMap
{
    public function register($entity, $data) { return $this; }

    public function unregister($entity) { return $this; }

    public function getEntity($className, $id) { return null; }

    public function contains($entity) { return false; }

    public function getOriginalData($entity) { return null; }

    public function updateOriginalData($entity, $data) { return $this; }

    public function clear() { return $this; }

}

class UnitOfWorkMock extends UnitOfWork
{
    public function persist($entity, $cas = null) { return $this; }

    public function delete($entity) { return $this; }

    public function insert($entity) { return $this; }

    public function commit($entity = null) { return $this; }

    public function clear() { return $this; }

}

class EntityManagerMock extends EntityManager
{
    public function __construct(\Couchbase $couchbase)
    {
        $this->im = new IdentityMapMock();
        $this->uow = new UnitOfWorkMock($this, $this->im);
        $this->cb = $couchbase;
    }

    public function getIm() { return $this->im; }
    public function getUoW() { return $this->uow; }

    public function persist($entity /*, todo $ttl ??? */) { return $this; }

    public function delete($entity) { return $this; }

    public function refresh($entity, $concurrent = false) { return $this; }

    public function flush() { return $this; }

    public function clear() { return $this; }

    public function update($entity, $callback /*, $arg1, $arg2 */) { return $this; }

}
