
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
#include "kernel/memory.h"
#include "kernel/object.h"
#include "kernel/exception.h"
#include "kernel/fcall.h"
#include "kernel/array.h"
#include "kernel/operators.h"


ZEPHIR_INIT_CLASS(Ouchbase_IdentityMap) {

	ZEPHIR_REGISTER_CLASS(Ouchbase, IdentityMap, ouchbase, identitymap, ouchbase_identitymap_method_entry, 0);

	/**
	 * @var \Ouchbase\Entity[]
	 */
	zend_declare_property_null(ouchbase_identitymap_ce, SL("entities"), ZEND_ACC_PRIVATE TSRMLS_CC);

	/**
	 * @var array
	 */
	zend_declare_property_null(ouchbase_identitymap_ce, SL("originalData"), ZEND_ACC_PRIVATE TSRMLS_CC);

	return SUCCESS;

}

PHP_METHOD(Ouchbase_IdentityMap, __construct) {

	zval *_0, *_1;

	ZEPHIR_MM_GROW();

	ZEPHIR_INIT_VAR(_0);
	array_init(_0);
	zephir_update_property_this(this_ptr, SL("entities"), _0 TSRMLS_CC);
	ZEPHIR_INIT_VAR(_1);
	array_init(_1);
	zephir_update_property_this(this_ptr, SL("originalData"), _1 TSRMLS_CC);
	ZEPHIR_MM_RESTORE();

}

/**
 * @param \Ouchbase\Entity entity
 * @param array data
 * @return this
 * @throws \Ouchbase\Exception\EntityLogicException
 */
PHP_METHOD(Ouchbase_IdentityMap, register) {

	zend_class_entry *_3;
	int ZEPHIR_LAST_CALL_STATUS;
	zephir_nts_static zephir_fcall_cache_entry *_0 = NULL;
	zval *entity, *data, *hash = NULL, *_1, *_2, *_4;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 2, 0, &entity, &data);



	if (!(zephir_instance_of_ev(entity, ouchbase_entity_ce TSRMLS_CC))) {
		ZEPHIR_THROW_EXCEPTION_DEBUG_STR(spl_ce_InvalidArgumentException, "Parameter 'entity' must be an instance of 'Ouchbase\\Entity'", "", 0);
		return;
	}
	ZEPHIR_CALL_CE_STATIC(&hash, ouchbase__etc_ce, "getentityhash", &_0, entity);
	zephir_check_call_status();
	_1 = zephir_fetch_nproperty_this(this_ptr, SL("entities"), PH_NOISY_CC);
	if (zephir_array_isset(_1, hash)) {
		ZEPHIR_INIT_VAR(_2);
		_3 = zend_fetch_class(SL("Ouchbase\\EntityLogicException"), ZEND_FETCH_CLASS_AUTO TSRMLS_CC);
		object_init_ex(_2, _3);
		if (zephir_has_constructor(_2 TSRMLS_CC)) {
			ZEPHIR_INIT_VAR(_4);
			ZVAL_STRING(_4, "is already registered in the identity map", 0);
			ZEPHIR_CALL_METHOD(NULL, _2, "__construct", NULL, entity, _4);
			zephir_check_temp_parameter(_4);
			zephir_check_call_status();
		}
		zephir_throw_exception_debug(_2, "ouchbase/IdentityMap.zep", 32 TSRMLS_CC);
		ZEPHIR_MM_RESTORE();
		return;
	}
	zephir_update_property_array(this_ptr, SL("entities"), hash, entity TSRMLS_CC);
	zephir_update_property_array(this_ptr, SL("originalData"), hash, data TSRMLS_CC);
	RETURN_THIS();

}

/**
 * @param \Ouchbase\Entity entity
 * @return this
 * @throws \Ouchbase\Exception\EntityLogicException
 */
PHP_METHOD(Ouchbase_IdentityMap, unregister) {

	zend_class_entry *_3;
	int ZEPHIR_LAST_CALL_STATUS;
	zephir_nts_static zephir_fcall_cache_entry *_0 = NULL;
	zval *entity, *hash = NULL, *_1, *_2, *_4, *_5, *_6;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &entity);



	if (!(zephir_instance_of_ev(entity, ouchbase_entity_ce TSRMLS_CC))) {
		ZEPHIR_THROW_EXCEPTION_DEBUG_STR(spl_ce_InvalidArgumentException, "Parameter 'entity' must be an instance of 'Ouchbase\\Entity'", "", 0);
		return;
	}
	ZEPHIR_CALL_CE_STATIC(&hash, ouchbase__etc_ce, "getentityhash", &_0, entity);
	zephir_check_call_status();
	_1 = zephir_fetch_nproperty_this(this_ptr, SL("entities"), PH_NOISY_CC);
	if (!(zephir_array_isset(_1, hash))) {
		ZEPHIR_INIT_VAR(_2);
		_3 = zend_fetch_class(SL("Ouchbase\\EntityLogicException"), ZEND_FETCH_CLASS_AUTO TSRMLS_CC);
		object_init_ex(_2, _3);
		if (zephir_has_constructor(_2 TSRMLS_CC)) {
			ZEPHIR_INIT_VAR(_4);
			ZVAL_STRING(_4, "is not registered in the identity map", 0);
			ZEPHIR_CALL_METHOD(NULL, _2, "__construct", NULL, entity, _4);
			zephir_check_temp_parameter(_4);
			zephir_check_call_status();
		}
		zephir_throw_exception_debug(_2, "ouchbase/IdentityMap.zep", 51 TSRMLS_CC);
		ZEPHIR_MM_RESTORE();
		return;
	}
	_5 = zephir_fetch_nproperty_this(this_ptr, SL("entities"), PH_NOISY_CC);
	zephir_array_unset(&_5, hash, PH_SEPARATE);
	_6 = zephir_fetch_nproperty_this(this_ptr, SL("originalData"), PH_NOISY_CC);
	zephir_array_unset(&_6, hash, PH_SEPARATE);
	RETURN_THIS();

}

/**
 * @param \Ouchbase\Entity entity
 * @return bool
 */
PHP_METHOD(Ouchbase_IdentityMap, contains) {

	int ZEPHIR_LAST_CALL_STATUS;
	zephir_nts_static zephir_fcall_cache_entry *_2 = NULL;
	zval *entity, *_0, *_1 = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &entity);



	if (!(zephir_instance_of_ev(entity, ouchbase_entity_ce TSRMLS_CC))) {
		ZEPHIR_THROW_EXCEPTION_DEBUG_STR(spl_ce_InvalidArgumentException, "Parameter 'entity' must be an instance of 'Ouchbase\\Entity'", "", 0);
		return;
	}
	_0 = zephir_fetch_nproperty_this(this_ptr, SL("entities"), PH_NOISY_CC);
	ZEPHIR_CALL_CE_STATIC(&_1, ouchbase__etc_ce, "getentityhash", &_2, entity);
	zephir_check_call_status();
	RETURN_MM_BOOL(zephir_array_isset(_0, _1));

}

/**
 * @param string className
 * @param int|string id
 * @return \Ouchbase\Entity|null
 */
PHP_METHOD(Ouchbase_IdentityMap, getEntity) {

	int ZEPHIR_LAST_CALL_STATUS;
	zephir_nts_static zephir_fcall_cache_entry *_2 = NULL;
	zval *className_param = NULL, *id, *entity, *_0, *_1 = NULL;
	zval *className = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 2, 0, &className_param, &id);

	zephir_get_strval(className, className_param);


	_0 = zephir_fetch_nproperty_this(this_ptr, SL("entities"), PH_NOISY_CC);
	ZEPHIR_CALL_CE_STATIC(&_1, ouchbase__etc_ce, "getentityhash", &_2, className, id);
	zephir_check_call_status();
	if (zephir_array_isset_fetch(&entity, _0, _1, 1 TSRMLS_CC)) {
		RETURN_CTOR(entity);
	}
	RETURN_MM_NULL();

}

/**
 * @param \Ouchbase\Entity entity
 * @return array|null
 */
PHP_METHOD(Ouchbase_IdentityMap, getOriginalData) {

	int ZEPHIR_LAST_CALL_STATUS;
	zephir_nts_static zephir_fcall_cache_entry *_2 = NULL;
	zval *entity, *data, *_0, *_1 = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &entity);



	if (!(zephir_instance_of_ev(entity, ouchbase_entity_ce TSRMLS_CC))) {
		ZEPHIR_THROW_EXCEPTION_DEBUG_STR(spl_ce_InvalidArgumentException, "Parameter 'entity' must be an instance of 'Ouchbase\\Entity'", "", 0);
		return;
	}
	_0 = zephir_fetch_nproperty_this(this_ptr, SL("originalData"), PH_NOISY_CC);
	ZEPHIR_CALL_CE_STATIC(&_1, ouchbase__etc_ce, "getentityhash", &_2, entity);
	zephir_check_call_status();
	if (zephir_array_isset_fetch(&data, _0, _1, 1 TSRMLS_CC)) {
		RETURN_CTOR(data);
	}
	RETURN_MM_NULL();

}

/**
 * @param \Ouchbase\Entity entity
 * @param array data
 * @return this
 */
PHP_METHOD(Ouchbase_IdentityMap, updateOriginalData) {

	int ZEPHIR_LAST_CALL_STATUS;
	zephir_nts_static zephir_fcall_cache_entry *_1 = NULL;
	zval *entity, *data, *_0 = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 2, 0, &entity, &data);



	if (!(zephir_instance_of_ev(entity, ouchbase_entity_ce TSRMLS_CC))) {
		ZEPHIR_THROW_EXCEPTION_DEBUG_STR(spl_ce_InvalidArgumentException, "Parameter 'entity' must be an instance of 'Ouchbase\\Entity'", "", 0);
		return;
	}
	ZEPHIR_CALL_CE_STATIC(&_0, ouchbase__etc_ce, "getentityhash", &_1, entity);
	zephir_check_call_status();
	zephir_update_property_array(this_ptr, SL("originalData"), _0, data TSRMLS_CC);
	RETURN_THIS();

}

/**
 * @return this
 */
PHP_METHOD(Ouchbase_IdentityMap, clear) {

	zval *_0, *_1;

	ZEPHIR_MM_GROW();

	ZEPHIR_INIT_VAR(_0);
	array_init(_0);
	zephir_update_property_this(this_ptr, SL("entities"), _0 TSRMLS_CC);
	ZEPHIR_INIT_VAR(_1);
	array_init(_1);
	zephir_update_property_this(this_ptr, SL("originalData"), _1 TSRMLS_CC);
	RETURN_THIS();

}

