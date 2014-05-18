
#ifdef HAVE_CONFIG_H
#include "../../ext_config.h"
#endif

#include <php.h>
#include "../../php_ext.h"
#include "../../ext.h"

#include <Zend/zend_operators.h>
#include <Zend/zend_exceptions.h>
#include <Zend/zend_interfaces.h>

#include "kernel/main.h"
#include "kernel/object.h"
#include "kernel/exception.h"
#include "kernel/fcall.h"
#include "kernel/memory.h"
#include "kernel/operators.h"


ZEPHIR_INIT_CLASS(Ouchbase_Exception_EntityModifiedException) {

	ZEPHIR_REGISTER_CLASS_EX(Ouchbase\\Exception, EntityModifiedException, ouchbase, exception_entitymodifiedexception, ouchbase_exception_entitylogicexception_ce, ouchbase_exception_entitymodifiedexception_method_entry, 0);

	/**
	 * Insert, delete or update
	 * @var string
	 */
	zend_declare_property_null(ouchbase_exception_entitymodifiedexception_ce, SL("action"), ZEND_ACC_PRIVATE TSRMLS_CC);

	/**
	 * Modified entity
	 * @var \Ouchbase\Entity
	 */
	zend_declare_property_null(ouchbase_exception_entitymodifiedexception_ce, SL("entity"), ZEND_ACC_PRIVATE TSRMLS_CC);

	zend_declare_class_constant_string(ouchbase_exception_entitymodifiedexception_ce, SL("ACTION_INSERT"), "insert" TSRMLS_CC);

	zend_declare_class_constant_string(ouchbase_exception_entitymodifiedexception_ce, SL("ACTION_DELETE"), "delete" TSRMLS_CC);

	zend_declare_class_constant_string(ouchbase_exception_entitymodifiedexception_ce, SL("ACTION_UPDATE"), "update" TSRMLS_CC);

	return SUCCESS;

}

PHP_METHOD(Ouchbase_Exception_EntityModifiedException, __construct) {

	zephir_nts_static zephir_fcall_cache_entry *_1 = NULL;
	zend_bool _0;
	int code, ZEPHIR_LAST_CALL_STATUS;
	zval *message = NULL;
	zval *entity, *message_param = NULL, *code_param = NULL, *previous = NULL, *_2;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 3, &entity, &message_param, &code_param, &previous);

	if (!message_param) {
		ZEPHIR_INIT_VAR(message);
		ZVAL_STRING(message, "", 1);
	} else {
		zephir_get_strval(message, message_param);
	}
	if (!code_param) {
		code = 0;
	} else {
		code = zephir_get_intval(code_param);
	}
	if (!previous) {
		previous = ZEPHIR_GLOBAL(global_null);
	}


	if (!(zephir_instance_of_ev(entity, ouchbase_entity_ce TSRMLS_CC))) {
		ZEPHIR_THROW_EXCEPTION_DEBUG_STR(spl_ce_InvalidArgumentException, "Parameter 'entity' must be an instance of 'Ouchbase\\Entity'", "", 0);
		return;
	}
	_0 = Z_TYPE_P(previous) != IS_NULL;
	if (_0) {
		_0 = !zephir_is_instance_of(previous, SL("Ouchbase\\Exception\\Exception") TSRMLS_CC);
	}
	if (_0) {
		ZEPHIR_THROW_EXCEPTION_DEBUG_STR(spl_ce_InvalidArgumentException, "Parameter 'previous' must be an instance of 'Ouchbase\\Exception\\Exception'", "", 0);
		return;
	}
	zephir_update_property_this(this_ptr, SL("entity"), entity TSRMLS_CC);
	ZEPHIR_INIT_VAR(_2);
	ZVAL_LONG(_2, code);
	ZEPHIR_CALL_PARENT(NULL, ouchbase_exception_entitymodifiedexception_ce, this_ptr, "__construct", &_1, entity, message, _2, previous);
	zephir_check_call_status();
	ZEPHIR_MM_RESTORE();

}

/**
 * @return string
 */
PHP_METHOD(Ouchbase_Exception_EntityModifiedException, getAction) {


	RETURN_MEMBER(this_ptr, "action");

}

/**
 * Insert, delete or update
 * @param string action
 * @return this
 */
PHP_METHOD(Ouchbase_Exception_EntityModifiedException, setAction) {

	zval *action;

	zephir_fetch_params(0, 1, 0, &action);



	zephir_update_property_this(this_ptr, SL("action"), action TSRMLS_CC);
	RETURN_THISW();

}

/**
 * @return \Ouchbase\Entity
 */
PHP_METHOD(Ouchbase_Exception_EntityModifiedException, getEntity) {


	RETURN_MEMBER(this_ptr, "entity");

}

