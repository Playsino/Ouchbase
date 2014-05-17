namespace Ouchbase;

class EntityProxy implements \Ouchbase\Entity
{
    /**
     * @var callable
     */
    private creator;

    /**
     * @var \Ouchbase\Entity
     */
    private entity = null;

    /**
     * @var string
     */
    private id;

    /**
     * @param callable creator
     * @param int|string id
     * @return \Ouchbase\Entity\Proxy
     */
    public function __construct(creator, id=null)
    {
        let this->creator = creator;
        let this->id = id;
    }

    /**
     * @return int|string
     */
    public function getId() -> string|int
    {
        if !this->id {
            let this->id = this->getEntity()->getId();
        }

        return this->id;
    }

    /**
     * @return \Ouchbase\Entity
     * @throws \Ouchbase\Exception\EntityLogicException
     */
    public function getEntity() -> <\Ouchbase\Entity>
    {
        if !this->entity {
            let this->entity = call_user_func_array(this->creator, []);

            if !this->entity {
                throw new \Ouchbase\Exception\EntityLogicException("Object was not created");
            }

            let this->creator = null;
        }

        return this->entity;
    }

    /**
     * @return bool
     */
    public function isProxied() -> boolean
    {
        return this->entity !== null;
    }

    public function __get(string property)
    {
        return this->getEntity()->{property};
    }

    public function __set(string property, value)
    {
        var entity;
        let entity = this->getEntity(),
            entity->{property} = value;
    }

    public function __call(string method, args)
    {
        return call_user_func_array([this->getEntity(), method], args);
    }

    public function __invoke()
    {
        return call_user_func_array([this->getEntity(), "__invoke"], func_get_args());
    }

}