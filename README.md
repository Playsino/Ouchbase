Ouchbase
========

Ouchbase is an object key/value mapper (OKVM) for Couchbase. It is written in [Zephir](https://github.com/phalcon/zephir) which allows you to write high performance PHP extensions without the headaches and timewastage of a C development cycle.

Installation
------------
Go to the ext direcotry and execute
```bash
sudo phpize
./configure
make
make install
```
If you have Zephir installed then just execute build.sh.

Usage
-----
```php
class TestEntity implements \Ouchbase\Entity
{
    private $id;

    public $property;

    public function __construct($id, $property)
    {
        $this->id = $id;
        $this->property = $property;
    }

    public function getId()
    {
        return $this->id;
    }

    public function getProperty()
    {
        return $this->property;
    }
}

class TestEntityRepository extends \Ouchbase\Repository
{
    public $keyPrefix = 'test:';

    protected $className = 'OuchbaseTest\TestEntity';

    public function toObject($data)
    {
        return new TestEntity($data['id'], $data['property']);
    }

    public function toArray($entity)
    {
        return array(
            'id' => $entity->getId(),
            'property' => $entity->getProperty(),
        );
    }
}
```

```php
$em = new \Ouchbase\EntityManager(new \Couchbase('localhost'));
$em->registerManagedEntityClass('OuchbaseTest\TestEntity', 'OuchbaseTest\TestEntityRepository');

$entity = new TestEntity('test-id', array('hello' => 'world'));

$em->persist($entity);
$em->flush();

$entity->property = array('world' => 'hello');
$em->flush();

$em->delete($entity);
$em->flush();
```

You can find more examples in test/OuchbaseTest/OuchbaseTest.php

Documentation
-------------
Please check stub.php to see Ouchbase API with documentation.