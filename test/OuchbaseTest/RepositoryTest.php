<?php

namespace OuchbaseTest;

require_once __DIR__ . '/../_etc.php';

class RepositoryTest extends \PHPUnit_Framework_TestCase
{
    /**
     * @var \OuchbaseTest\TestEntityRepository
     */
    private $repository;

    /**
     * @var \Couchbase
     */
    private static $_cb;

    /*
     * @var \Ouchbase\EntityManager
     */
    private $_em;

    /*
     * @var \Ouchbase\EntityManager
     */
    private $_im;

    /*
     * @var \Ouchbase\EntityManager
     */
    private $_uow;

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

    /**
     * @return \Ouchbase\EntityManager|\PHPUnit_Framework_MockObject_MockObject
     */
    protected function getEntityManagerMock()
    {
        if (!$this->_em) {
            $this->_em = $this->getMock('Ouchbase\EntityManager', array(), array($this->getCb()));
            $this->_em->expects($this->any())->method('persist')->will($this->returnSelf());
            $this->_em->expects($this->any())->method('delete')->will($this->returnSelf());
            $this->_em->expects($this->any())->method('refresh')->will($this->returnSelf());
            $this->_em->expects($this->any())->method('update')->will($this->returnSelf());
            $this->_em->expects($this->any())->method('flush')->will($this->returnSelf());
            $this->_em->expects($this->any())->method('clear')->will($this->returnSelf());
        }

        return $this->_em;
    }

    /**
     * @return \Ouchbase\IdentityMap|\PHPUnit_Framework_MockObject_MockObject
     */
    protected function getIdentityMapMock()
    {
        if (!$this->_im) {
            $this->_im = $this->getMock('Ouchbase\IdentityMap');
            $this->_im->expects($this->any())->method('register')->will($this->returnSelf());
            $this->_im->expects($this->any())->method('unregister')->will($this->returnSelf());
            $this->_im->expects($this->any())->method('getEntity')->will($this->returnValue(null));
            //$this->_im->expects($this->any())->method('contains')->will($this->returnValue(false));
            //$this->_im->expects($this->any())->method('getOriginalData')->will($this->returnValue(null));
            $this->_im->expects($this->any())->method('updateOriginalData')->will($this->returnSelf());
            $this->_im->expects($this->any())->method('clear')->will($this->returnSelf());
        }

        return $this->_im;
    }

    /**
     * @return \Ouchbase\UnitOfWork|\PHPUnit_Framework_MockObject_MockObject
     */
    protected function getUnitOfWorkMock()
    {
        if (!$this->_uow) {
            $this->_uow = $this->getMock('Ouchbase\UnitOfWork', array(), array(
                $this->getEntityManagerMock(),
                $this->getIdentityMapMock()
            ));
            $this->_uow->expects($this->any())->method('persist')->will($this->returnSelf());
            $this->_uow->expects($this->any())->method('delete')->will($this->returnSelf());
            $this->_uow->expects($this->any())->method('insert')->will($this->returnSelf());
            $this->_uow->expects($this->any())->method('commit')->will($this->returnSelf());
            $this->_uow->expects($this->any())->method('clear')->will($this->returnSelf());
        }

        return $this->_uow;
    }

    protected function setUp()
    {
        $this->repository = new TestEntityRepository(
            $this->getUnitOfWorkMock(),
            $this->getIdentityMapMock(),
            $this->getCb()
        );
    }

    public function testInsert()
    {
        $entity = new TestEntity('test-id', 'test-value');
        $this->repository->insert($entity);

        $data = $this->getCb()->get($this->repository->getKey($entity->getId()));

        $this->assertJson($data);
        $this->assertJsonStringEqualsJsonString(json_encode(array(
            'id' => $entity->getId(),
            'property' => $entity->getProperty(),
        )), $data);

        $this->getCb()->delete($this->repository->getKey($entity->getId()));
    }

    /**
     * @depends testInsert
     */
    public function testFind()
    {
        $entity = new TestEntity('test-id', 'test-value');
        $this->repository->insert($entity);

        $found = $this->repository->find('test-id');

        $this->assertInstanceOf('OuchbaseTest\TestEntity', $found);
        $this->assertEquals($entity->getId(), $found->getId());
        $this->assertEquals($entity->getProperty(), $found->getProperty());

        $this->getCb()->delete($this->repository->getKey($entity->getId()));
    }

    /**
     * @depends testInsert
     */
    public function testRefresh()
    {
        $this->getIdentityMapMock()
            ->expects($this->once())
            ->method('contains')
            ->will($this->returnValue(true));

        $entity = new TestEntity('test-id', 'test-value');
        $this->repository->insert($entity);

        $this->getCb()->set($this->repository->getKey($entity->getId()), json_encode(array(
            'id' => $entity->getId(),
            'property' => 42,
        )));

        $this->repository->refresh($entity);

        $this->assertEquals($entity->getId(), $entity->getId());
        $this->assertEquals(42, $entity->getProperty());

        $this->getCb()->delete($this->repository->getKey($entity->getId()));
    }

    /**
     * @depends testInsert
     */
    public function testFindAll()
    {
        $entity1 = new TestEntity('test-id-1', 'test-value-1');
        $entity2 = new TestEntity('test-id-2', 'test-value-2');

        $this->repository->insert($entity1);
        $this->repository->insert($entity2);

        $found = $this->repository->findAll(array('test-id-1', 'test-id-2'));

        $this->assertNotEmpty($found);
        $this->assertCount(2, $found);

        $this->assertEquals($entity1->getId(), $found[0]->getId());
        $this->assertEquals($entity1->getProperty(), $found[0]->getProperty());

        $this->assertEquals($entity2->getId(), $found[1]->getId());
        $this->assertEquals($entity2->getProperty(), $found[1]->getProperty());

        $this->getCb()->delete($this->repository->getKey($entity1->getId()));
        $this->getCb()->delete($this->repository->getKey($entity2->getId()));
    }

    /**
     * @depends testInsert
     */
    public function testUpdate()
    {
        $this->getIdentityMapMock()
            ->expects($this->once())
            ->method('getOriginalData')
            ->will($this->returnValue(array(
                'id' => 'test-id',
                'property' => 'test-value'
            )));

        $entity = new TestEntity('test-id', 'test-value');
        $this->repository->insert($entity);

        $entity->property = 42;
        $this->repository->update($entity);

        $data = $this->getCb()->get($this->repository->getKey($entity->getId()));

        $this->assertJson($data);
        $this->assertJsonStringEqualsJsonString(json_encode(array(
            'id' => $entity->getId(),
            'property' => 42,
        )), $data);

        $this->getCb()->delete($this->repository->getKey($entity->getId()));
    }

    /**
     * @depends testInsert
     */
    public function testDelete()
    {
        $entity = new TestEntity('test-id', 'test-value');
        $this->repository->insert($entity);
        $this->repository->delete($entity);

        $data = $this->getCb()->get($this->repository->getKey($entity->getId()));

        $this->assertEmpty($data);
    }

}