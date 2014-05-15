<?php

namespace OuchbaseTest;

require_once __DIR__ . '/../_etc.php';

class EntityTest extends \PHPUnit_Framework_TestCase
{
    public function testGetId()
    {
        $entity = new TestEntity('test-id', 'test-value');
        $this->assertEquals('test-id', $entity->getId());
    }

}