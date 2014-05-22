Ouchbase
========

Ouchbase is an object key/value mapper (OKVM) for Couchbase. It is written in [Zephir](https://github.com/phalcon/zephir) which allows you to write high performance PHP extensions without the headaches and timewastage of a C development cycle.

Installation
------------
Just clone Ouchbase repository and run `./install.sh`. If you have Zephir installed then you can execute `/.build.sh.`

To install Ouchbase with composer add the following to your composer.json
```
"require": {
    "ihor/ouchbase": "dev-master"
},
"scripts": {
    "post-install-cmd": ["./vendor/ihor/ouchbase/install.sh"],
    "post-update-cmd": ["./vendor/ihor/ouchbase/install.sh"]
},
```

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

    public function findByProperty($property) { /** @todo */ }

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

$em = new \Ouchbase\EntityManager(new \Couchbase('localhost'));
$em->registerManagedEntityClass('TestEntity', 'TestEntityRepository');

$entity = new TestEntity('test-id', array('hello' => 'world'));

$em->persist($entity);
$em->flush();

$entity->property = array('world' => 'hello');
$em->flush();

$em->delete($entity);
$em->flush();

$entities = $em->getRepository('TestEntity')->findByProperty(42);
```

You can find more examples in test/OuchbaseTest/OuchbaseTest.php

Documentation
-------------
Please check stub.php to see Ouchbase API with documentation. Also use stub.php for autocompletion in your favourite IDE.
