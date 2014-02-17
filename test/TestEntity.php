<?php

namespace OuchbaseTest;

class TestEntity implements \Ouchbase\Entity
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