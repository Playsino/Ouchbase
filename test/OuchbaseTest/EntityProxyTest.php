<?php

namespace OuchbaseTest;

require_once __DIR__ . '/../_etc.php';

class EntityProxyTest extends \PHPUnit_Framework_TestCase
{
    /**
     * @var \Ouchbase\EntityProxy|TestEntity
     */
    private $proxy;

    protected function setUp()
    {
        $this->proxy = new \Ouchbase\EntityProxy(function() {
            return new TestEntity('test-id', 'test-value');
        }, 'test-id');
    }

    public function testGetId()
    {
        $this->assertEquals('test-id', $this->proxy->getId());
    }

    public function testGet()
    {
        $this->assertEquals('test-value', $this->proxy->property);
    }

    public function testSet()
    {
        $this->proxy->property = 'new-test-value';
        $this->assertEquals('new-test-value', $this->proxy->property);
        $this->assertEquals('new-test-value', $this->proxy->getEntity()->property);
    }

    public function testCall()
    {
        $this->assertEquals('test-value', $this->proxy->getProperty());
    }

}