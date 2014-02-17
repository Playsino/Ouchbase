<?php

namespace Ouchbase;

interface EntityConverter
{
    /**
     * @param Entity $entity
     * @return array
     */
    public function toArray(Entity $entity);

    /**
     * @param array $data
     * @return Entity
     */
    public function toObject(array $data);

}