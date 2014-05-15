<?php

namespace OuchbaseTest;

require_once __DIR__ . '/../_etc.php';

class EntityManagerTest extends \PHPUnit_Framework_TestCase
{
    /**
     * @var \Ouchbase\EntityManager
     */
    private $em;

    /**
     * @var \Couchbase
     */
    private static $_cb;

    /**
     * @return \Couchbase
     */
    protected function getCb()
    {
        if (!self::$_cb) {
            self::$_cb = new \Couchbase('localhost');
        }

        return self::$_cb;
    }

    protected function setUp()
    {
        $this->em = new \Ouchbase\EntityManager($this->getCb());
    }

    public function testRegisterManagedEntityClass()
    {
        $this->em->registerManagedEntityClass('OuchbaseTest\TestEntity', 'OuchbaseTest\TestEntityRepository');
        $this->assertInstanceOf('OuchbaseTest\TestEntityRepository', $this->em->getRepository('OuchbaseTest\TestEntity'));
        $this->assertInstanceOf('OuchbaseTest\TestEntityRepository', $this->em->getRepository(new TestEntity('test-id', 42)));
    }

    /**
     * @expectedException \Ouchbase\Exception\EntityManagerException
     */
    public function testRegisterManagedEntityClassInExceptionalSituation()
    {
        $this->em->getRepository('OuchbaseTest\TestEntity');
    }

}