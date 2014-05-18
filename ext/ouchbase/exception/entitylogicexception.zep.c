
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


ZEPHIR_INIT_CLASS(Ouchbase_Exception_EntityLogicException) {

	ZEPHIR_REGISTER_CLASS_EX(Ouchbase\\Exception, EntityLogicException, ouchbase, exception_entitylogicexception, spl_ce_LogicException, ouchbase_exception_entitylogicexception_method_entry, 0);

	return SUCCESS;

}

PHP_METHOD(Ouchbase_Exception_EntityLogicException, __construct) {

	zephir_nts_static zephir_fcall_cache_entry *_2 = NULL, *_6 = NULL;
	zend_bool _0;
	int code, ZEPHIR_LAST_CALL_STATUS;
	zval *message = NULL;
	zval *entity, *message_param = NULL, *code_param = NULL, *previous = NULL, *_1 = NULL, *_3 = NULL, _4, *_5 = NULL, *_7;

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
	ZEPHIR_CALL_CE_STATIC(&_1, ouchbase__etc_ce, "getentityclass", &_2, entity);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&_3, entity, "getid",  NULL);
	zephir_check_call_status();
	ZEPHIR_SINIT_VAR(_4);
	ZVAL_STRING(&_4, "%s with id '%s' %s", 0);
	ZEPHIR_CALL_FUNCTION(&_5, "sprintf", &_6, &_4, _1, _3, message);
	zephir_check_call_status();
	ZEPHIR_INIT_VAR(_7);
	ZVAL_LONG(_7, code);
	ZEPHIR_CALL_PARENT(NULL, ouchbase_exception_entitylogicexception_ce, this_ptr, "__construct", NULL, _5, _7, previous);
	zephir_check_call_status();
	ZEPHIR_MM_RESTORE();

}

