<?php

namespace OuchbaseTest;

require_once '_etc.php';

class IdentityMapTest extends \PHPUnit_Framework_TestCase
{
    /**
     * @var \Ouchbase\IdentityMap
     */
    private $im;

    protected function setUp()
    {
        $this->im = new \Ouchbase\IdentityMap();
    }

    public function testRegisterAndContains()
    {
        $entity = new TestEntity('test-id', 'test-value');

        $this->im->register($entity, array('id' => 'test-id', 'property' => 'test-value'));
        $this->assertTrue($this->im->contains($entity));

        $this->im->unregister($entity);
        $this->assertFalse($this->im->contains($entity));
    }

    public function testGetEntity()
    {
        $entity = new TestEntity('test-id', 'test-value');

        $this->im->register($entity, array('id' => 'test-id', 'property' => 'test-value'));
        $this->assertEquals($entity, $this->im->getEntity('OuchbaseTest\TestEntity', 'test-id'));
    }

    public function testGetOriginalData()
    {
        $entity = new TestEntity('test-id', 'test-value');

        $this->im->register($entity, array('id' => 'test-id', 'property' => 'test-value'));
        $this->assertEquals(array('id' => 'test-id', 'property' => 'test-value'), $this->im->getOriginalData($entity));
    }

    public function testUpdateOriginalData()
    {
        $entity = new TestEntity('test-id', 'test-value');

        $this->im->register($entity, array('id' => 'test-id', 'property' => 'test-value'));
        $this->im->updateOriginalData($entity, array('id' => 'test-id', 'property' => 'another-value'));
        $this->assertEquals(array('id' => 'test-id', 'property' => 'another-value'), $this->im->getOriginalData($entity));
    }

    public function testClear()
    {
        $entity = new TestEntity('test-id', 'test-value');

        $this->im->register($entity, array('id' => 'test-id', 'property' => 'test-value'));
        $this->im->clear();

        $this->assertFalse($this->im->contains($entity));
        $this->assertEquals(null, $this->im->getOriginalData($entity));
    }

}