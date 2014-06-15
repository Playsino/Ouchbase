
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
#include "kernel/operators.h"
#include "kernel/fcall.h"
#include "kernel/exception.h"
#include "kernel/array.h"


ZEPHIR_INIT_CLASS(Ouchbase_EntityProxy) {

	ZEPHIR_REGISTER_CLASS(Ouchbase, EntityProxy, ouchbase, entityproxy, ouchbase_entityproxy_method_entry, 0);

	/**
	 * @var callable
	 */
	zend_declare_property_null(ouchbase_entityproxy_ce, SL("creator"), ZEND_ACC_PRIVATE TSRMLS_CC);

	/**
	 * @var \Ouchbase\Entity
	 */
	zend_declare_property_null(ouchbase_entityproxy_ce, SL("entity"), ZEND_ACC_PRIVATE TSRMLS_CC);

	/**
	 * @var string
	 */
	zend_declare_property_null(ouchbase_entityproxy_ce, SL("id"), ZEND_ACC_PRIVATE TSRMLS_CC);

	zend_class_implements(ouchbase_entityproxy_ce TSRMLS_CC, 1, ouchbase_entity_ce);
	return SUCCESS;

}

/**
 * @param callable creator
 * @param int|string id
 * @return \Ouchbase\Entity\Proxy
 */
PHP_METHOD(Ouchbase_EntityProxy, __construct) {

	zval *creator, *id = NULL;

	zephir_fetch_params(0, 1, 1, &creator, &id);

	if (!id) {
		id = ZEPHIR_GLOBAL(global_null);
	}


	zephir_update_property_this(this_ptr, SL("creator"), creator TSRMLS_CC);
	zephir_update_property_this(this_ptr, SL("id"), id TSRMLS_CC);

}

/**
 * @return int|string
 */
PHP_METHOD(Ouchbase_EntityProxy, getId) {

	int ZEPHIR_LAST_CALL_STATUS;
	zval *_0, *_1 = NULL, *_2 = NULL;

	ZEPHIR_MM_GROW();

	_0 = zephir_fetch_nproperty_this(this_ptr, SL("id"), PH_NOISY_CC);
	if (!(zephir_is_true(_0))) {
		ZEPHIR_CALL_METHOD(&_1, this_ptr, "getentity",  NULL);
		zephir_check_call_status();
		ZEPHIR_CALL_METHOD(&_2, _1, "getid",  NULL);
		zephir_check_call_status();
		zephir_update_property_this(this_ptr, SL("id"), _2 TSRMLS_CC);
	}
	RETURN_MM_MEMBER(this_ptr, "id");

}

/**
 * @return \Ouchbase\Entity
 * @throws \Ouchbase\Exception\EntityLogicException
 */
PHP_METHOD(Ouchbase_EntityProxy, getEntity) {

	int ZEPHIR_LAST_CALL_STATUS;
	zval *_0, *_1, *_2, *_3, *_4;

	ZEPHIR_MM_GROW();

	_0 = zephir_fetch_nproperty_this(this_ptr, SL("entity"), PH_NOISY_CC);
	if (!(zephir_is_true(_0))) {
		ZEPHIR_INIT_VAR(_1);
		_2 = zephir_fetch_nproperty_this(this_ptr, SL("creator"), PH_NOISY_CC);
		ZEPHIR_INIT_VAR(_3);
		array_init(_3);
		ZEPHIR_CALL_USER_FUNC_ARRAY(_1, _2, _3);
		zephir_check_call_status();
		zephir_update_property_this(this_ptr, SL("entity"), _1 TSRMLS_CC);
		_4 = zephir_fetch_nproperty_this(this_ptr, SL("entity"), PH_NOISY_CC);
		if (!(zephir_is_true(_4))) {
			ZEPHIR_THROW_EXCEPTION_DEBUG_STR(ouchbase_exception_entitylogicexception_ce, "Object was not created", "ouchbase/EntityProxy.zep", 53);
			return;
		}
		zephir_update_property_this(this_ptr, SL("creator"), ZEPHIR_GLOBAL(global_null) TSRMLS_CC);
	}
	RETURN_MM_MEMBER(this_ptr, "entity");

}

/**
 * @return bool
 */
PHP_METHOD(Ouchbase_EntityProxy, isProxied) {

	zval *_0;


	_0 = zephir_fetch_nproperty_this(this_ptr, SL("entity"), PH_NOISY_CC);
	RETURN_BOOL(Z_TYPE_P(_0) != IS_NULL);

}

PHP_METHOD(Ouchbase_EntityProxy, __get) {

	int ZEPHIR_LAST_CALL_STATUS;
	zval *property_param = NULL, *_0 = NULL, *_1;
	zval *property = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &property_param);

	zephir_get_strval(property, property_param);


	ZEPHIR_CALL_METHOD(&_0, this_ptr, "getentity",  NULL);
	zephir_check_call_status();
	ZEPHIR_OBS_VAR(_1);
	zephir_read_property_zval(&_1, _0, property, PH_NOISY_CC);
	RETURN_CCTOR(_1);

}

PHP_METHOD(Ouchbase_EntityProxy, __set) {

	int ZEPHIR_LAST_CALL_STATUS;
	zval *property_param = NULL, *value, *entity = NULL;
	zval *property = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 2, 0, &property_param, &value);

	zephir_get_strval(property, property_param);


	ZEPHIR_CALL_METHOD(&entity, this_ptr, "getentity",  NULL);
	zephir_check_call_status();
	zephir_update_property_zval_zval(entity, property, value TSRMLS_CC);
	ZEPHIR_MM_RESTORE();

}

PHP_METHOD(Ouchbase_EntityProxy, __call) {

	zval *_0;
	int ZEPHIR_LAST_CALL_STATUS;
	zval *method_param = NULL, *args, *_1 = NULL;
	zval *method = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 2, 0, &method_param, &args);

	zephir_get_strval(method, method_param);


	ZEPHIR_INIT_VAR(_0);
	array_init_size(_0, 3);
	ZEPHIR_CALL_METHOD(&_1, this_ptr, "getentity",  NULL);
	zephir_check_call_status();
	zephir_array_fast_append(_0, _1);
	zephir_array_fast_append(_0, method);
	ZEPHIR_CALL_USER_FUNC_ARRAY(return_value, _0, args);
	zephir_check_call_status();
	RETURN_MM();

}

PHP_METHOD(Ouchbase_EntityProxy, __invoke) {

	zephir_nts_static zephir_fcall_cache_entry *_3 = NULL;
	zval *_1 = NULL, *_2;
	zval *_0;
	int ZEPHIR_LAST_CALL_STATUS;

	ZEPHIR_MM_GROW();

	ZEPHIR_INIT_VAR(_0);
	array_init_size(_0, 3);
	ZEPHIR_CALL_METHOD(&_1, this_ptr, "getentity",  NULL);
	zephir_check_call_status();
	zephir_array_fast_append(_0, _1);
	ZEPHIR_INIT_VAR(_2);
	ZVAL_STRING(_2, "__invoke", 1);
	zephir_array_fast_append(_0, _2);
	ZEPHIR_CALL_FUNCTION(&_1, "func_get_args", &_3);
	zephir_check_call_status();
	ZEPHIR_CALL_USER_FUNC_ARRAY(return_value, _0, _1);
	zephir_check_call_status();
	RETURN_MM();

}

