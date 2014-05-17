namespace Ouchbase;

class _etc
{
    /**
     * @param Entity entity
     * @return string
     */
    public static function getEntityClass(entity) -> string
    {
        if entity instanceof \Ouchbase\EntityProxy {
            return get_class(entity->getEntity());
        }

        return get_class(entity);
    }

    /**
     * @param string|Entity className
     * @param int|string|null id
     * @return string
     */
    public static function getEntityHash(className, id = null) -> string
    {
        if is_object(className) {
            return self::getEntityClass(className) . ":" . className->getId();
        }

        return className . ":" . id;
    }

}