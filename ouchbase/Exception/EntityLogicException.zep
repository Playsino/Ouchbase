namespace Ouchbase\Exception;

class EntityLogicException extends \LogicException
{
    public function __construct(<\Ouchbase\Entity> entity, string message = "", int code = 0, <Exception> previous = null)
    {
        parent::__construct(
            sprintf("%s with id '%s' %s", \Ouchbase\_etc::getEntityClass(entity), entity->getId(), message),
            code,
            previous
        );
    }

}
