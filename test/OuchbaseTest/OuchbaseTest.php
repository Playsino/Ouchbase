<?php

namespace OuchbaseTest;

require_once __DIR__ . '/../_etc.php';

class OuchbaseTest extends \PHPUnit_Framework_TestCase
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
        $this->em->registerManagedEntityClass('OuchbaseTest\TestEntity', 'OuchbaseTest\TestEntityRepository');
    }

    public function testCrud()
    {
        $entity = new TestEntity('test-id', array('h' => 4, 'w' => 2));

        $this->em->persist($entity);
        $this->em->flush();
        $this->em->clear();

        /** @var TestEntity $inserted */
        $inserted = $this->em->getRepository($entity)->find($entity->getId());

        $this->assertEquals($entity->getId(), $inserted->getId());
        $this->assertEquals($entity->getProperty(), $inserted->getProperty());
        $this->assertNotSame($entity, $inserted);

        $inserted->property = array('h' => 4, 'w' => 2, 'x' => 1337);
        $this->em->flush();
        $this->em->clear();

        /** @var TestEntity $updated */
        $updated = $this->em->getRepository($entity)->find($entity->getId());

        $this->assertEquals($inserted->getId(), $updated->getId());
        $this->assertEquals($inserted->getProperty(), $updated->getProperty());
        $this->assertNotSame($inserted, $updated);

        $this->em->delete($updated);
        $this->em->flush();

        $deleted = $this->em->getRepository($entity)->find($entity->getId());
        $this->assertEquals(null, $deleted);
    }

    /**
     * @expectedException \Ouchbase\Exception\EntityModifiedException
     */
    public function testCas()
    {
        $entity = new TestEntity('test-id', array('h' => 4, 'w' => 2));

        $this->em->persist($entity);
        $this->em->flush();
        $this->em->clear();

        /** @var TestEntity $inserted */
        $inserted = $this->em->getRepository($entity)->find($entity->getId(), true);

        // Modify entity outside of Ouchbase
        $this->getCb()->replace(
            $this->em->getRepository($entity)->getKey($entity->getId()),
            json_encode(array('id' => $entity->getId(), 'property' => array('h' => 2, 'w' => 4)))
        );

        $inserted->property = array('h' => 4, 'w' => 2, 'x' => 1337);
        $this->em->flush();
        $this->em->clear();
    }

}