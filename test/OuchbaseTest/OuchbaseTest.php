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

        /** @var TestEntity $found1 */
        /** @var TestEntity $found2 */
        $found1 = $this->em->getRepository($entity1)->find($entity1->getId());
        $found2 = $this->em->getRepository($entity2)->find($entity2->getId(), true);

        // Modify entity 2 outside of Ouchbase
        $this->getCb()->replace(
            $this->em->getRepository($entity2)->getKey($entity2->getId()),
            json_encode(array('id' => $entity2->getId(), 'property' => array('h' => 2, 'w' => 4)))
        );

        $found1->property = array('h' => 2, 'w' => 4);
        $found2->property = array(2 => 'h', 4 => 'w');

        try {
            $this->em->flush();
        }
        catch (\Ouchbase\Exception\EntityModifiedException $e) {
            $this->assertSame($e->getEntity(), $found2);
            $this->assertSame($e->getAction(), \Ouchbase\Exception\EntityModifiedException::ACTION_UPDATE);
        }

        /** @var TestEntity $externallyModified1 */
        /** @var TestEntity $externallyModified2 */
        $externallyModified1 = $this->em->getRepository($entity1)->find($entity1->getId());
        $externallyModified2 = $this->em->getRepository($entity2)->find($entity2->getId());

        $this->assertEquals($entity1, $externallyModified1);
        $this->assertEquals($found1->getId(), $externallyModified1->getId());
        $this->assertNotEquals($found1->getProperty(), $externallyModified1->getProperty());

        $this->assertEquals($entity2->getId(), $externallyModified2->getId());
        $this->assertNotEquals($entity2->getProperty(), $externallyModified2->getProperty());
        $this->assertEquals($found2->getId(), $externallyModified2->getId());
        $this->assertNotEquals($found2->getProperty(), $externallyModified2->getProperty());
        $this->assertEquals(array('h' => 2, 'w' => 4), $externallyModified2->getProperty());

        $this->getCb()->delete($this->em->getRepository($entity1)->getKey($entity1->getId()));
        $this->getCb()->delete($this->em->getRepository($entity2)->getKey($entity2->getId()));
    }

    public function testDeleteRollback()
    {
        $entity1 = new TestEntity('test-id-1', array('h' => 'w'));
        $entity2 = new TestEntity('test-id-2', array(4 => 2));
        $entity3 = new TestEntity('test-id-3', array(13 => 37));

        $this->em->persist($entity1);
        $this->em->persist($entity2);
        $this->em->persist($entity3);
        $this->em->flush();
        $this->em->clear();

        /** @var TestEntity $found1 */
        /** @var TestEntity $found2 */
        /** @var TestEntity $found3 */
        $found1 = $this->em->getRepository($entity1)->find($entity1->getId());
        $found2 = $this->em->getRepository($entity2)->find($entity2->getId());
        $found3 = $this->em->getRepository($entity3)->find($entity3->getId(), true);

        // Modify entity 3 outside of Ouchbase
        $this->getCb()->replace(
            $this->em->getRepository($entity3)->getKey($entity3->getId()),
            json_encode(array('id' => $entity3->getId(), 'property' => array(37 => 13)))
        );

        $found1->property = array('w' => 'h');
        $this->em->delete($found2);
        $this->em->delete($found3);

        try {
            $this->em->flush();
        }
        catch (\Ouchbase\Exception\EntityModifiedException $e) {
            $this->assertSame($e->getEntity(), $found3);
            $this->assertSame($e->getAction(), \Ouchbase\Exception\EntityModifiedException::ACTION_DELETE);
        }

        /** @var TestEntity $insertedEntity2 */
        /** @var TestEntity $insertedEntity2 */
        /** @var TestEntity $insertedEntity2 */
        $externallyModified1 = $this->em->getRepository($entity1)->find($entity1->getId());
        $externallyModified2 = $this->em->getRepository($entity2)->find($entity2->getId());
        $externallyModified3 = $this->em->getRepository($entity3)->find($entity3->getId());

        $this->assertEquals($entity1, $externallyModified1);
        $this->assertNotEquals($found1, $externallyModified1);
        $this->assertNotEquals($externallyModified2, null);
        $this->assertEquals($entity2, $externallyModified2);
        $this->assertNotEquals($entity3, $externallyModified3);

        $this->getCb()->delete($this->em->getRepository($entity1)->getKey($entity1->getId()));
        $this->getCb()->delete($this->em->getRepository($entity2)->getKey($entity2->getId()));
        $this->getCb()->delete($this->em->getRepository($entity3)->getKey($entity3->getId()));
    }

    public function testAtomicUpdate()
    {
        $entity = new TestEntity('test-id', array('h' => 4, 'w' => 2));

        $this->em->persist($entity);
        $this->em->flush();

        $this->em->update($entity, function(TestEntity $entity) {
            $entity->property = array(4 => 'h', 2 => 'w');
        });
        $this->em->clear();

        /** @var TestEntity $updated */
        $updated = $this->em->getRepository($entity)->find($entity->getId());
        $this->assertEquals($entity->getId(), $updated->getId());
        $this->assertEquals(array(4 => 'h', 2 => 'w'), $updated->getProperty());

        $this->getCb()->delete($this->em->getRepository($entity)->getKey($entity->getId()));
    }
}