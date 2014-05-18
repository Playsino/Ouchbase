
#ifdef HAVE_CONFIG_H
#include "../ext_config.h"
#endif

#include <php.h>
#include "../php_ext.h"
#include "../ext.h"

#include <Zend/zend_operators.h>
#include <Zend/zend_exceptions.h>
#include <Zend/zend_interfaces.h>

#include "kernel/main.h"
#include "kernel/object.h"
#include "kernel/memory.h"
#include "kernel/fcall.h"
#include "kernel/concat.h"


ZEPHIR_INIT_CLASS(Ouchbase__etc) {

	ZEPHIR_REGISTER_CLASS(Ouchbase, _etc, ouchbase, _etc, ouchbase__etc_method_entry, 0);

	return SUCCESS;

}

/**
 * @param Entity entity
 * @return string
 */
PHP_METHOD(Ouchbase__etc, getEntityClass) {

	int ZEPHIR_LAST_CALL_STATUS;
	zval *entity, *_0 = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &entity);



	if (zephir_instance_of_ev(entity, ouchbase_entityproxy_ce TSRMLS_CC)) {
		ZEPHIR_CALL_METHOD(&_0, entity, "getentity",  NULL);
		zephir_check_call_status();
		zephir_get_class(return_value, _0, 0 TSRMLS_CC);
		RETURN_MM();
	}
	zephir_get_class(return_value, entity, 0 TSRMLS_CC);
	RETURN_MM();

}

/**
 * @param string|Entity className
 * @param int|string|null id
 * @return string
 */
PHP_METHOD(Ouchbase__etc, getEntityHash) {

	int ZEPHIR_LAST_CALL_STATUS;
	zval *className, *id = NULL, *_0 = NULL, *_1 = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 1, &className, &id);

	if (!id) {
		id = ZEPHIR_GLOBAL(global_null);
	}


	if (Z_TYPE_P(className) == IS_OBJECT) {
		ZEPHIR_CALL_SELF(&_0, "getentityclass", NULL, className);
		zephir_check_call_status();
		ZEPHIR_CALL_METHOD(&_1, className, "getid",  NULL);
		zephir_check_call_status();
		ZEPHIR_CONCAT_VSV(return_value, _0, ":", _1);
		RETURN_MM();
	}
	ZEPHIR_CONCAT_VSV(return_value, className, ":", id);
	RETURN_MM();

}

