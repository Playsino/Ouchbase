
#ifdef HAVE_CONFIG_H
#include "../ext_config.h"
#endif

#include <php.h>
#include "../php_ext.h"
#include "../ext.h"

#include <Zend/zend_exceptions.h>

#include "kernel/main.h"


ZEPHIR_INIT_CLASS(Ouchbase_Entity) {

	ZEPHIR_REGISTER_INTERFACE(Ouchbase, Entity, ouchbase, entity, ouchbase_entity_method_entry);

	return SUCCESS;

}

/**
 * @return int|string
 */
ZEPHIR_DOC_METHOD(Ouchbase_Entity, getId);

