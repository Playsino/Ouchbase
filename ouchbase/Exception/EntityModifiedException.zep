namespace Ouchbase\Exception;

class EntityModifiedException extends \Ouchbase\Exception\EntityLogicException
{
    const ACTION_INSERT = "insert";
    const ACTION_DELETE = "delete";
    const ACTION_UPDATE = "update";

    /**
     * Insert, delete or update
     * @var string
     */
    private action;

    /**
     * Modified entity
     * @var \Ouchbase\Entity
     */
    private entity;

    public function __construct(<Ouchbase\Entity> entity, string message = "", int code = 0, <Exception> previous = null)
    {
        let this->entity = entity;
        parent::__construct(entity, message, code, previous);
    }


    /**
     * @return string
     */
    public function getAction() -> string
    {
        return this->action;
    }

    /**
     * Insert, delete or update
     * @param string action
     * @return this
     */
    public function setAction(action) -> <Ouchbase\Exception\EntityModifiedException>
    {
        let this->action = action;
        return this;
    }

    /**
     * @return \Ouchbase\Entity
     */
    public function getEntity() -> <Ouchbase\Entity>
    {
        return this->entity;
    }

}
