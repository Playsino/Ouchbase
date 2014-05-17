<?php

namespace OuchbaseTest;

use Ouchbase\Entity;
use Ouchbase\Repository;

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
    public $keyPrefix = 'test:';

    /**
     * @var string
     */
    protected $className = 'OuchbaseTest\TestEntity';

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