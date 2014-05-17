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

    public function testUpdateRollback()
    {
        $entity1 = new TestEntity('test-id-1', array('h' => 4, 'w' => 2));
        $entity2 = new TestEntity('test-id-2', array('x' => 1337));

        $this->em->persist($entity1);
        $this->em->persist($entity2);
        $this->em->flush();
        $this->em->clear();

        /** @var TestEntity $inserted1 */
        $inserted1 = $this->em->getRepository($entity1)->find($entity1->getId());

        /** @var TestEntity $inserted2 */
        $inserted2 = $this->em->getRepository($entity2)->find($entity2->getId(), true);

        // Modify entity 2 outside of Ouchbase
        $this->getCb()->replace(
            $this->em->getRepository($entity2)->getKey($entity2->getId()),
            json_encode(array('id' => $entity2->getId(), 'property' => array('h' => 2, 'w' => 4)))
        );

        $inserted1->property = array('h' => 2, 'w' => 4);
        $inserted2->property = array(2 => 'h', 4 => 'w');

        try {
            $this->em->flush();
        }
        catch (\Ouchbase\Exception\EntityModifiedException $e) {
            $this->assertSame($e->getEntity(), $inserted2);
            $this->assertSame($e->getAction(), \Ouchbase\Exception\EntityModifiedException::ACTION_UPDATE);
        }

        /** @var TestEntity $externallyModified1 */
        $externallyModified1 = $this->em->getRepository($entity1)->find($entity1->getId());

        /** @var TestEntity $externallyModified2 */
        $externallyModified2 = $this->em->getRepository($entity2)->find($entity2->getId());

        $this->assertEquals($entity1->getId(), $externallyModified1->getId());
        $this->assertEquals($entity1->getProperty(), $externallyModified1->getProperty());
        $this->assertEquals($inserted1->getId(), $externallyModified1->getId());
        $this->assertNotEquals($inserted1->getProperty(), $externallyModified1->getProperty());

        $this->assertEquals($entity2->getId(), $externallyModified2->getId());
        $this->assertNotEquals($entity2->getProperty(), $externallyModified2->getProperty());
        $this->assertEquals($inserted2->getId(), $externallyModified2->getId());
        $this->assertNotEquals($inserted2->getProperty(), $externallyModified2->getProperty());
        $this->assertEquals(array('h' => 2, 'w' => 4), $externallyModified2->getProperty());
    }

}