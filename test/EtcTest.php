<?php

namespace OuchbaseTest;

use Ouchbase\_etc;

require_once '_etc.php';

class EtcTest extends \PHPUnit_Framework_TestCase
{
    public function testGetEntityClass()
    {
        $entity = new TestEntity('test-id', 'test-value');
        $this->assertEquals('OuchbaseTest\TestEntity', _etc::getEntityClass($entity));

        $someEntityProxy = new \Ouchbase\EntityProxy(function() use ($entity) { return $entity; });
        $this->assertEquals('OuchbaseTest\TestEntity', _etc::getEntityClass($someEntityProxy));
    }

    public function testGetEntityHash()
    {
        $someEntity = new TestEntity('test-id', 'test-value');
        $this->assertEquals('OuchbaseTest\TestEntity:test-id', _etc::getEntityHash($someEntity));

        $someEntityProxy = new \Ouchbase\EntityProxy(function() use ($someEntity) { return $someEntity; });
        $this->assertEquals('OuchbaseTest\TestEntity:test-id', _etc::getEntityHash($someEntityProxy));

        $this->assertEquals('OuchbaseTest\TestEntity:test-id', _etc::getEntityHash('OuchbaseTest\TestEntity', 'test-id'));
    }

}