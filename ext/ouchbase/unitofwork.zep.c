
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
#include "kernel/exception.h"
#include "kernel/memory.h"
#include "kernel/array.h"
#include "kernel/fcall.h"
#include "kernel/operators.h"
#include "kernel/hash.h"

ZEPHIR_INIT_CLASS(Ouchbase_UnitOfWork) {

	ZEPHIR_REGISTER_CLASS(Ouchbase, UnitOfWork, ouchbase, unitofwork, ouchbase_unitofwork_method_entry, 0);

	/**
	 * @var \Ouchbase\IdentityMap
	 */
	zend_declare_property_null(ouchbase_unitofwork_ce, SL("im"), ZEND_ACC_PRIVATE TSRMLS_CC);

	/**
	 * @var \Ouchbase\EntityManager
	 */
	zend_declare_property_null(ouchbase_unitofwork_ce, SL("em"), ZEND_ACC_PRIVATE TSRMLS_CC);

	/**
	 * @var \Ouchbase\Entity[]
	 */
	zend_declare_property_null(ouchbase_unitofwork_ce, SL("persisted"), ZEND_ACC_PRIVATE TSRMLS_CC);

	/**
	 * @var \Ouchbase\Entity[]
	 */
	zend_declare_property_null(ouchbase_unitofwork_ce, SL("inserted"), ZEND_ACC_PRIVATE TSRMLS_CC);

	/**
	 * @var \Ouchbase\Entity[]
	 */
	zend_declare_property_null(ouchbase_unitofwork_ce, SL("deleted"), ZEND_ACC_PRIVATE TSRMLS_CC);

	return SUCCESS;

}

/**
 * @param \Ouchbase\EntityManager entityManager
 * @param \Ouchbase\IdentityMap identityMap
 */
PHP_METHOD(Ouchbase_UnitOfWork, __construct) {

	zval *entityManager, *identityMap, *_0, *_1, *_2;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 2, 0, &entityManager, &identityMap);



	if (!(zephir_instance_of_ev(entityManager, ouchbase_entitymanager_ce TSRMLS_CC))) {
		ZEPHIR_THROW_EXCEPTION_DEBUG_STR(spl_ce_InvalidArgumentException, "Parameter 'entityManager' must be an instance of 'Ouchbase\\EntityManager'", "", 0);
		return;
	}
	if (!(zephir_instance_of_ev(identityMap, ouchbase_identitymap_ce TSRMLS_CC))) {
		ZEPHIR_THROW_EXCEPTION_DEBUG_STR(spl_ce_InvalidArgumentException, "Parameter 'identityMap' must be an instance of 'Ouchbase\\IdentityMap'", "", 0);
		return;
	}
	zephir_update_property_this(this_ptr, SL("em"), entityManager TSRMLS_CC);
	zephir_update_property_this(this_ptr, SL("im"), identityMap TSRMLS_CC);
	ZEPHIR_INIT_VAR(_0);
	array_init(_0);
	zephir_update_property_this(this_ptr, SL("persisted"), _0 TSRMLS_CC);
	ZEPHIR_INIT_VAR(_1);
	array_init(_1);
	zephir_update_property_this(this_ptr, SL("inserted"), _1 TSRMLS_CC);
	ZEPHIR_INIT_VAR(_2);
	array_init(_2);
	zephir_update_property_this(this_ptr, SL("deleted"), _2 TSRMLS_CC);
	ZEPHIR_MM_RESTORE();

}

/**
 * @param \Ouchbase\Entity entity
 * @param string|null cas
 * @throws \Ouchbase\Exception\EntityLogicException
 * @return this
 */
PHP_METHOD(Ouchbase_UnitOfWork, persist) {

	zval *_5;
	int ZEPHIR_LAST_CALL_STATUS;
	zephir_nts_static zephir_fcall_cache_entry *_2 = NULL;
	zval *entity, *cas = NULL, *_0, *_1 = NULL, *_3, *_4, *_6 = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 1, &entity, &cas);

	if (!cas) {
		cas = ZEPHIR_GLOBAL(global_null);
	}


	if (!(zephir_instance_of_ev(entity, ouchbase_entity_ce TSRMLS_CC))) {
		ZEPHIR_THROW_EXCEPTION_DEBUG_STR(spl_ce_InvalidArgumentException, "Parameter 'entity' must be an instance of 'Ouchbase\\Entity'", "", 0);
		return;
	}
	_0 = zephir_fetch_nproperty_this(this_ptr, SL("deleted"), PH_NOISY_CC);
	ZEPHIR_CALL_CE_STATIC(&_1, ouchbase__etc_ce, "getentityhash", &_2, entity);
	zephir_check_call_status();
	if (zephir_array_isset(_0, _1)) {
		ZEPHIR_INIT_VAR(_3);
		object_init_ex(_3, ouchbase_exception_entitylogicexception_ce);
		ZEPHIR_INIT_VAR(_4);
		ZVAL_STRING(_4, "was marked as deleted", 0);
		ZEPHIR_CALL_METHOD(NULL, _3, "__construct", NULL, entity, _4);
		zephir_check_temp_parameter(_4);
		zephir_check_call_status();
		zephir_throw_exception_debug(_3, "ouchbase/UnitOfWork.zep", 49 TSRMLS_CC);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(_5);
	array_init_size(_5, 3);
	zephir_array_fast_append(_5, entity);
	zephir_array_fast_append(_5, cas);
	ZEPHIR_CALL_CE_STATIC(&_6, ouchbase__etc_ce, "getentityhash", &_2, entity);
	zephir_check_call_status();
	zephir_update_property_array(this_ptr, SL("persisted"), _6, _5 TSRMLS_CC);
	RETURN_THIS();

}

/**
 * @param \Ouchbase\Entity entity
 * @throws \Ouchbase\Exception\EntityLogicException
 * @return this
 */
PHP_METHOD(Ouchbase_UnitOfWork, delete) {

	int ZEPHIR_LAST_CALL_STATUS;
	zephir_nts_static zephir_fcall_cache_entry *_0 = NULL;
	zval *entity, *hash = NULL, *_1, *_2, *_3, *_4, *_5, *_6;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &entity);



	if (!(zephir_instance_of_ev(entity, ouchbase_entity_ce TSRMLS_CC))) {
		ZEPHIR_THROW_EXCEPTION_DEBUG_STR(spl_ce_InvalidArgumentException, "Parameter 'entity' must be an instance of 'Ouchbase\\Entity'", "", 0);
		return;
	}
	ZEPHIR_CALL_CE_STATIC(&hash, ouchbase__etc_ce, "getentityhash", &_0, entity);
	zephir_check_call_status();
	_1 = zephir_fetch_nproperty_this(this_ptr, SL("persisted"), PH_NOISY_CC);
	if (!(zephir_array_isset(_1, hash))) {
		ZEPHIR_INIT_VAR(_2);
		object_init_ex(_2, ouchbase_exception_entitylogicexception_ce);
		ZEPHIR_INIT_VAR(_3);
		ZVAL_STRING(_3, "was not persisted", 0);
		ZEPHIR_CALL_METHOD(NULL, _2, "__construct", NULL, entity, _3);
		zephir_check_temp_parameter(_3);
		zephir_check_call_status();
		zephir_throw_exception_debug(_2, "ouchbase/UnitOfWork.zep", 67 TSRMLS_CC);
		ZEPHIR_MM_RESTORE();
		return;
	}
	_4 = zephir_fetch_nproperty_this(this_ptr, SL("persisted"), PH_NOISY_CC);
	zephir_array_fetch(&_5, _4, hash, PH_NOISY | PH_READONLY TSRMLS_CC);
	zephir_update_property_array(this_ptr, SL("deleted"), hash, _5 TSRMLS_CC);
	_6 = zephir_fetch_nproperty_this(this_ptr, SL("persisted"), PH_NOISY_CC);
	zephir_array_unset(&_6, hash, PH_SEPARATE);
	RETURN_THIS();

}

/**
 * @param \Ouchbase\Entity entity
 * @return this
 */
PHP_METHOD(Ouchbase_UnitOfWork, insert) {

	int ZEPHIR_LAST_CALL_STATUS;
	zephir_nts_static zephir_fcall_cache_entry *_1 = NULL;
	zval *entity, *_0 = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &entity);



	if (!(zephir_instance_of_ev(entity, ouchbase_entity_ce TSRMLS_CC))) {
		ZEPHIR_THROW_EXCEPTION_DEBUG_STR(spl_ce_InvalidArgumentException, "Parameter 'entity' must be an instance of 'Ouchbase\\Entity'", "", 0);
		return;
	}
	ZEPHIR_CALL_CE_STATIC(&_0, ouchbase__etc_ce, "getentityhash", &_1, entity);
	zephir_check_call_status();
	zephir_update_property_array(this_ptr, SL("inserted"), _0, entity TSRMLS_CC);
	RETURN_THIS();

}

/**
 * @param \Ouchbase\Entity|null entity If entity is not managed no exception will be thrown
 * @throws \Ouchbase\Exception\EntityModifiedException
 */
PHP_METHOD(Ouchbase_UnitOfWork, commit) {

	zephir_nts_static zephir_fcall_cache_entry *_3 = NULL, *_4 = NULL, *_5 = NULL, *_8 = NULL, *_10 = NULL;
	int ZEPHIR_LAST_CALL_STATUS;
	zend_bool _0;
	zval *entity = NULL, *e = NULL, *im = NULL, *_1, *_2, *_6 = NULL, *_7 = NULL, *_9 = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 0, 1, &entity);

	if (!entity) {
		entity = ZEPHIR_GLOBAL(global_null);
	}


	_0 = Z_TYPE_P(entity) != IS_NULL;
	if (_0) {
		_0 = !zephir_instance_of_ev(entity, ouchbase_entity_ce TSRMLS_CC);
	}
	if (_0) {
		ZEPHIR_THROW_EXCEPTION_DEBUG_STR(spl_ce_InvalidArgumentException, "Parameter 'entity' must be an instance of 'Ouchbase\\Entity'", "", 0);
		return;
	}

	/* try_start_1: */

		_1 = zephir_fetch_nproperty_this(this_ptr, SL("im"), PH_NOISY_CC);
		ZEPHIR_INIT_VAR(_2);
		if (zephir_clone(_2, _1 TSRMLS_CC) == FAILURE) {
			RETURN_MM();
		}
		ZEPHIR_CPY_WRT(im, _2);
		ZEPHIR_CALL_METHOD(NULL, this_ptr, "commitupdates", &_3, entity);
		zephir_check_call_status_or_jump(try_end_1);
		ZEPHIR_CALL_METHOD(NULL, this_ptr, "commitdeletes", &_4, entity);
		zephir_check_call_status_or_jump(try_end_1);
		ZEPHIR_CALL_METHOD(NULL, this_ptr, "commitinserts", &_5, entity);
		zephir_check_call_status_or_jump(try_end_1);
		RETURN_THIS();

	try_end_1:

	ZEPHIR_CPY_WRT(e, EG(exception));
	if (zephir_is_instance_of(e, SL("Ouchbase\\Exception\\EntityModifiedException") TSRMLS_CC)) {
		zend_clear_exception(TSRMLS_C);
		if (Z_TYPE_P(entity) != IS_NULL) {
			zephir_throw_exception_debug(e, "ouchbase/UnitOfWork.zep", 110 TSRMLS_CC);
			ZEPHIR_MM_RESTORE();
			return;
		}
		ZEPHIR_CALL_METHOD(&_6, e, "getaction",  NULL);
		zephir_check_call_status();
		if (ZEPHIR_IS_STRING(_6, "update")) {
			ZEPHIR_CALL_METHOD(&_7, e, "getentity",  NULL);
			zephir_check_call_status();
			ZEPHIR_CALL_METHOD(NULL, this_ptr, "rollbackupdates", &_8, im, _7);
			zephir_check_call_status();
		} else {
			ZEPHIR_CALL_METHOD(&_7, e, "getaction",  NULL);
			zephir_check_call_status();
			if (ZEPHIR_IS_STRING(_7, "delete")) {
				ZEPHIR_CALL_METHOD(NULL, this_ptr, "rollbackupdates", &_8, im);
				zephir_check_call_status();
				ZEPHIR_CALL_METHOD(&_9, e, "getentity",  NULL);
				zephir_check_call_status();
				ZEPHIR_CALL_METHOD(NULL, this_ptr, "rollbackdeletes", &_10, im, _9);
				zephir_check_call_status();
			}
		}
		_1 = zephir_fetch_nproperty_this(this_ptr, SL("em"), PH_NOISY_CC);
		ZEPHIR_CALL_METHOD(NULL, _1, "clear", NULL);
		zephir_check_call_status();
		zephir_throw_exception_debug(e, "ouchbase/UnitOfWork.zep", 128 TSRMLS_CC);
		ZEPHIR_MM_RESTORE();
		return;
	}
	if (zephir_instance_of_ev(e, zend_exception_get_default(TSRMLS_C) TSRMLS_CC)) {
		zend_clear_exception(TSRMLS_C);
		if (Z_TYPE_P(entity) != IS_NULL) {
			zephir_throw_exception_debug(e, "ouchbase/UnitOfWork.zep", 110 TSRMLS_CC);
			ZEPHIR_MM_RESTORE();
			return;
		}
		ZEPHIR_CALL_METHOD(&_6, e, "getaction",  NULL);
		zephir_check_call_status();
		if (ZEPHIR_IS_STRING(_6, "update")) {
			ZEPHIR_CALL_METHOD(&_7, e, "getentity",  NULL);
			zephir_check_call_status();
			ZEPHIR_CALL_METHOD(NULL, this_ptr, "rollbackupdates", &_8, im, _7);
			zephir_check_call_status();
		} else {
			ZEPHIR_CALL_METHOD(&_7, e, "getaction",  NULL);
			zephir_check_call_status();
			if (ZEPHIR_IS_STRING(_7, "delete")) {
				ZEPHIR_CALL_METHOD(NULL, this_ptr, "rollbackupdates", &_8, im);
				zephir_check_call_status();
				ZEPHIR_CALL_METHOD(&_9, e, "getentity",  NULL);
				zephir_check_call_status();
				ZEPHIR_CALL_METHOD(NULL, this_ptr, "rollbackdeletes", &_10, im, _9);
				zephir_check_call_status();
			}
		}
		_1 = zephir_fetch_nproperty_this(this_ptr, SL("em"), PH_NOISY_CC);
		ZEPHIR_CALL_METHOD(NULL, _1, "clear", NULL);
		zephir_check_call_status();
		zephir_throw_exception_debug(e, "ouchbase/UnitOfWork.zep", 128 TSRMLS_CC);
		ZEPHIR_MM_RESTORE();
		return;
	}
	RETURN_THIS();

}

/**
 * @param \Ouchbase\Entity|null entity
 * @return this
 */
PHP_METHOD(Ouchbase_UnitOfWork, commitInserts) {

	HashTable *_8;
	HashPosition _7;
	int ZEPHIR_LAST_CALL_STATUS;
	zephir_nts_static zephir_fcall_cache_entry *_1 = NULL;
	zend_bool _0, _2;
	zval *entity = NULL, *hash = NULL, *_3, *_4, *_5 = NULL, *_6, **_9, *_10;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 0, 1, &entity);

	if (!entity) {
		ZEPHIR_CPY_WRT(entity, ZEPHIR_GLOBAL(global_null));
	} else {
		ZEPHIR_SEPARATE_PARAM(entity);
	}


	_0 = Z_TYPE_P(entity) != IS_NULL;
	if (_0) {
		_0 = !zephir_instance_of_ev(entity, ouchbase_entity_ce TSRMLS_CC);
	}
	if (_0) {
		ZEPHIR_THROW_EXCEPTION_DEBUG_STR(spl_ce_InvalidArgumentException, "Parameter 'entity' must be an instance of 'Ouchbase\\Entity'", "", 0);
		return;
	}
	if (Z_TYPE_P(entity) != IS_NULL) {
		ZEPHIR_CALL_CE_STATIC(&hash, ouchbase__etc_ce, "getentityhash", &_1, entity);
		zephir_check_call_status();
		_2 = zephir_is_true(hash);
		if (_2) {
			_3 = zephir_fetch_nproperty_this(this_ptr, SL("inserted"), PH_NOISY_CC);
			_2 = zephir_array_isset(_3, hash);
		}
		if (_2) {
			_4 = zephir_fetch_nproperty_this(this_ptr, SL("em"), PH_NOISY_CC);
			ZEPHIR_CALL_METHOD(&_5, _4, "getrepository", NULL, entity);
			zephir_check_call_status();
			ZEPHIR_CALL_METHOD(NULL, _5, "insert", NULL, entity);
			zephir_check_call_status();
			_6 = zephir_fetch_nproperty_this(this_ptr, SL("inserted"), PH_NOISY_CC);
			zephir_array_unset(&_6, hash, PH_SEPARATE);
		}
		RETURN_THIS();
	}
	_3 = zephir_fetch_nproperty_this(this_ptr, SL("inserted"), PH_NOISY_CC);
	zephir_is_iterable(_3, &_8, &_7, 0, 0);
	for (
	  ; zephir_hash_get_current_data_ex(_8, (void**) &_9, &_7) == SUCCESS
	  ; zephir_hash_move_forward_ex(_8, &_7)
	) {
		ZEPHIR_GET_HVALUE(entity, _9);
		_4 = zephir_fetch_nproperty_this(this_ptr, SL("em"), PH_NOISY_CC);
		ZEPHIR_CALL_METHOD(&_5, _4, "getrepository", NULL, entity);
		zephir_check_call_status();
		ZEPHIR_CALL_METHOD(NULL, _5, "insert", NULL, entity);
		zephir_check_call_status();
	}
	ZEPHIR_INIT_VAR(_10);
	array_init(_10);
	zephir_update_property_this(this_ptr, SL("inserted"), _10 TSRMLS_CC);
	RETURN_THIS();

}

/**
 * @param \Ouchbase\Entity|null entity
 * @return this
 */
PHP_METHOD(Ouchbase_UnitOfWork, commitDeletes) {

	HashTable *_11;
	HashPosition _10;
	int ZEPHIR_LAST_CALL_STATUS;
	zephir_nts_static zephir_fcall_cache_entry *_1 = NULL;
	zend_bool _0, _2;
	zval *entity = NULL, *hash = NULL, *_3, *_4, *_5 = NULL, *_6, *_7, *_8, *_9, *data = NULL, **_12, *_13, *_14;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 0, 1, &entity);

	if (!entity) {
		entity = ZEPHIR_GLOBAL(global_null);
	}


	_0 = Z_TYPE_P(entity) != IS_NULL;
	if (_0) {
		_0 = !zephir_instance_of_ev(entity, ouchbase_entity_ce TSRMLS_CC);
	}
	if (_0) {
		ZEPHIR_THROW_EXCEPTION_DEBUG_STR(spl_ce_InvalidArgumentException, "Parameter 'entity' must be an instance of 'Ouchbase\\Entity'", "", 0);
		return;
	}
	if (Z_TYPE_P(entity) != IS_NULL) {
		ZEPHIR_CALL_CE_STATIC(&hash, ouchbase__etc_ce, "getentityhash", &_1, entity);
		zephir_check_call_status();
		_2 = zephir_is_true(hash);
		if (_2) {
			_3 = zephir_fetch_nproperty_this(this_ptr, SL("deleted"), PH_NOISY_CC);
			_2 = zephir_array_isset(_3, hash);
		}
		if (_2) {
			_4 = zephir_fetch_nproperty_this(this_ptr, SL("em"), PH_NOISY_CC);
			ZEPHIR_CALL_METHOD(&_5, _4, "getrepository", NULL, entity);
			zephir_check_call_status();
			_6 = zephir_fetch_nproperty_this(this_ptr, SL("deleted"), PH_NOISY_CC);
			zephir_array_fetch(&_7, _6, hash, PH_NOISY | PH_READONLY TSRMLS_CC);
			zephir_array_fetch_long(&_8, _7, 1, PH_NOISY | PH_READONLY TSRMLS_CC);
			ZEPHIR_CALL_METHOD(NULL, _5, "delete", NULL, entity, _8);
			zephir_check_call_status();
			_9 = zephir_fetch_nproperty_this(this_ptr, SL("deleted"), PH_NOISY_CC);
			zephir_array_unset(&_9, hash, PH_SEPARATE);
		}
		RETURN_THIS();
	}
	_3 = zephir_fetch_nproperty_this(this_ptr, SL("deleted"), PH_NOISY_CC);
	zephir_is_iterable(_3, &_11, &_10, 0, 0);
	for (
	  ; zephir_hash_get_current_data_ex(_11, (void**) &_12, &_10) == SUCCESS
	  ; zephir_hash_move_forward_ex(_11, &_10)
	) {
		ZEPHIR_GET_HVALUE(data, _12);
		_4 = zephir_fetch_nproperty_this(this_ptr, SL("em"), PH_NOISY_CC);
		zephir_array_fetch_long(&_7, data, 0, PH_NOISY | PH_READONLY TSRMLS_CC);
		ZEPHIR_CALL_METHOD(&_5, _4, "getrepository", NULL, _7);
		zephir_check_call_status();
		zephir_array_fetch_long(&_8, data, 0, PH_NOISY | PH_READONLY TSRMLS_CC);
		zephir_array_fetch_long(&_13, data, 1, PH_NOISY | PH_READONLY TSRMLS_CC);
		ZEPHIR_CALL_METHOD(NULL, _5, "delete", NULL, _8, _13);
		zephir_check_call_status();
	}
	ZEPHIR_INIT_VAR(_14);
	array_init(_14);
	zephir_update_property_this(this_ptr, SL("deleted"), _14 TSRMLS_CC);
	RETURN_THIS();

}

/**
 * @param \Ouchbase\Entity|null entity
 * @return this
 */
PHP_METHOD(Ouchbase_UnitOfWork, commitUpdates) {

	HashTable *_10;
	HashPosition _9;
	int ZEPHIR_LAST_CALL_STATUS;
	zephir_nts_static zephir_fcall_cache_entry *_1 = NULL;
	zend_bool _0, _2;
	zval *entity = NULL, *hash = NULL, *_3, *_4, *_5 = NULL, *_6, *_7, *_8, *data = NULL, **_11, *_12;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 0, 1, &entity);

	if (!entity) {
		entity = ZEPHIR_GLOBAL(global_null);
	}


	_0 = Z_TYPE_P(entity) != IS_NULL;
	if (_0) {
		_0 = !zephir_instance_of_ev(entity, ouchbase_entity_ce TSRMLS_CC);
	}
	if (_0) {
		ZEPHIR_THROW_EXCEPTION_DEBUG_STR(spl_ce_InvalidArgumentException, "Parameter 'entity' must be an instance of 'Ouchbase\\Entity'", "", 0);
		return;
	}
	if (Z_TYPE_P(entity) != IS_NULL) {
		ZEPHIR_CALL_CE_STATIC(&hash, ouchbase__etc_ce, "getentityhash", &_1, entity);
		zephir_check_call_status();
		_2 = zephir_is_true(hash);
		if (_2) {
			_3 = zephir_fetch_nproperty_this(this_ptr, SL("persisted"), PH_NOISY_CC);
			_2 = zephir_array_isset(_3, hash);
		}
		if (_2) {
			_4 = zephir_fetch_nproperty_this(this_ptr, SL("em"), PH_NOISY_CC);
			ZEPHIR_CALL_METHOD(&_5, _4, "getrepository", NULL, entity);
			zephir_check_call_status();
			_6 = zephir_fetch_nproperty_this(this_ptr, SL("persisted"), PH_NOISY_CC);
			zephir_array_fetch(&_7, _6, hash, PH_NOISY | PH_READONLY TSRMLS_CC);
			zephir_array_fetch_long(&_8, _7, 1, PH_NOISY | PH_READONLY TSRMLS_CC);
			ZEPHIR_CALL_METHOD(NULL, _5, "update", NULL, entity, _8);
			zephir_check_call_status();
		}
		RETURN_THIS();
	}
	_3 = zephir_fetch_nproperty_this(this_ptr, SL("persisted"), PH_NOISY_CC);
	zephir_is_iterable(_3, &_10, &_9, 0, 0);
	for (
	  ; zephir_hash_get_current_data_ex(_10, (void**) &_11, &_9) == SUCCESS
	  ; zephir_hash_move_forward_ex(_10, &_9)
	) {
		ZEPHIR_GET_HVALUE(data, _11);
		_4 = zephir_fetch_nproperty_this(this_ptr, SL("em"), PH_NOISY_CC);
		zephir_array_fetch_long(&_7, data, 0, PH_NOISY | PH_READONLY TSRMLS_CC);
		ZEPHIR_CALL_METHOD(&_5, _4, "getrepository", NULL, _7);
		zephir_check_call_status();
		zephir_array_fetch_long(&_8, data, 0, PH_NOISY | PH_READONLY TSRMLS_CC);
		zephir_array_fetch_long(&_12, data, 1, PH_NOISY | PH_READONLY TSRMLS_CC);
		ZEPHIR_CALL_METHOD(NULL, _5, "update", NULL, _8, _12);
		zephir_check_call_status();
	}
	RETURN_THIS();

}

/**
 * @param IdentityMap im
 * @param \Ouchbase\Entity entity
 * @return this
 */
PHP_METHOD(Ouchbase_UnitOfWork, rollbackUpdates) {

	zephir_fcall_cache_entry *_18 = NULL;
	HashTable *_4;
	HashPosition _3;
	int ZEPHIR_LAST_CALL_STATUS;
	zephir_nts_static zephir_fcall_cache_entry *_1 = NULL;
	zend_bool _0, _6;
	zval *im, *entity = NULL, *repository = NULL, *hash = NULL, *data = NULL, *_2, **_5, *_7 = NULL, *_8, *_9, *_10, *_11, *_12 = NULL, *_13 = NULL, *_14, *_15 = NULL, *_16 = NULL, *_17;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 1, &im, &entity);

	if (!entity) {
		entity = ZEPHIR_GLOBAL(global_null);
	}
	ZEPHIR_INIT_VAR(hash);
	ZVAL_NULL(hash);


	if (!(zephir_instance_of_ev(im, ouchbase_identitymap_ce TSRMLS_CC))) {
		ZEPHIR_THROW_EXCEPTION_DEBUG_STR(spl_ce_InvalidArgumentException, "Parameter 'im' must be an instance of 'Ouchbase\\IdentityMap'", "", 0);
		return;
	}
	_0 = Z_TYPE_P(entity) != IS_NULL;
	if (_0) {
		_0 = !zephir_instance_of_ev(entity, ouchbase_entity_ce TSRMLS_CC);
	}
	if (_0) {
		ZEPHIR_THROW_EXCEPTION_DEBUG_STR(spl_ce_InvalidArgumentException, "Parameter 'entity' must be an instance of 'Ouchbase\\Entity'", "", 0);
		return;
	}
	if (Z_TYPE_P(entity) != IS_NULL) {
		ZEPHIR_CALL_CE_STATIC(&hash, ouchbase__etc_ce, "getentityhash", &_1, entity);
		zephir_check_call_status();
	}
	_2 = zephir_fetch_nproperty_this(this_ptr, SL("persisted"), PH_NOISY_CC);
	zephir_is_iterable(_2, &_4, &_3, 0, 0);
	for (
	  ; zephir_hash_get_current_data_ex(_4, (void**) &_5, &_3) == SUCCESS
	  ; zephir_hash_move_forward_ex(_4, &_3)
	) {
		ZEPHIR_GET_HVALUE(data, _5);
		_6 = zephir_is_true(hash);
		if (_6) {
			zephir_array_fetch_long(&_8, data, 0, PH_NOISY | PH_READONLY TSRMLS_CC);
			ZEPHIR_CALL_CE_STATIC(&_7, ouchbase__etc_ce, "getentityhash", &_1, _8);
			zephir_check_call_status();
			_6 = ZEPHIR_IS_IDENTICAL(_7, hash);
		}
		if (_6) {
			break;
		}
		_9 = zephir_fetch_nproperty_this(this_ptr, SL("em"), PH_NOISY_CC);
		zephir_array_fetch_long(&_10, data, 0, PH_NOISY | PH_READONLY TSRMLS_CC);
		ZEPHIR_CALL_METHOD(&repository, _9, "getrepository", NULL, _10);
		zephir_check_call_status();
		_11 = zephir_fetch_nproperty_this(this_ptr, SL("em"), PH_NOISY_CC);
		ZEPHIR_CALL_METHOD(&_12, _11, "getconnection",  NULL);
		zephir_check_call_status();
		zephir_array_fetch_long(&_14, data, 0, PH_NOISY | PH_READONLY TSRMLS_CC);
		ZEPHIR_CALL_METHOD(&_15, _14, "getid",  NULL);
		zephir_check_call_status();
		ZEPHIR_CALL_METHOD(&_13, repository, "getkey", NULL, _15);
		zephir_check_call_status();
		zephir_array_fetch_long(&_17, data, 0, PH_NOISY | PH_READONLY TSRMLS_CC);
		ZEPHIR_CALL_METHOD(&_16, im, "getoriginaldata", &_18, _17);
		zephir_check_call_status();
		ZEPHIR_CALL_METHOD(NULL, _12, "replace", NULL, _13, _16);
		zephir_check_call_status();
	}
	RETURN_THIS();

}

/**
 * @param IdentityMap im
 * @param \Ouchbase\Entity entity
 * @return this
 */
PHP_METHOD(Ouchbase_UnitOfWork, rollbackDeletes) {

	zephir_fcall_cache_entry *_17 = NULL;
	zend_bool _5;
	HashTable *_3;
	HashPosition _2;
	int ZEPHIR_LAST_CALL_STATUS;
	zephir_nts_static zephir_fcall_cache_entry *_0 = NULL;
	zval *im, *entity, *repository = NULL, *hash = NULL, *data = NULL, *_1, **_4, *_6 = NULL, *_7, *_8, *_9, *_10, *_11 = NULL, *_12 = NULL, *_13, *_14 = NULL, *_15 = NULL, *_16;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 2, 0, &im, &entity);

	ZEPHIR_INIT_VAR(hash);
	ZVAL_NULL(hash);


	if (!(zephir_instance_of_ev(im, ouchbase_identitymap_ce TSRMLS_CC))) {
		ZEPHIR_THROW_EXCEPTION_DEBUG_STR(spl_ce_InvalidArgumentException, "Parameter 'im' must be an instance of 'Ouchbase\\IdentityMap'", "", 0);
		return;
	}
	if (!(zephir_instance_of_ev(entity, ouchbase_entity_ce TSRMLS_CC))) {
		ZEPHIR_THROW_EXCEPTION_DEBUG_STR(spl_ce_InvalidArgumentException, "Parameter 'entity' must be an instance of 'Ouchbase\\Entity'", "", 0);
		return;
	}
	if (Z_TYPE_P(entity) != IS_NULL) {
		ZEPHIR_CALL_CE_STATIC(&hash, ouchbase__etc_ce, "getentityhash", &_0, entity);
		zephir_check_call_status();
	}
	_1 = zephir_fetch_nproperty_this(this_ptr, SL("deleted"), PH_NOISY_CC);
	zephir_is_iterable(_1, &_3, &_2, 0, 0);
	for (
	  ; zephir_hash_get_current_data_ex(_3, (void**) &_4, &_2) == SUCCESS
	  ; zephir_hash_move_forward_ex(_3, &_2)
	) {
		ZEPHIR_GET_HVALUE(data, _4);
		_5 = zephir_is_true(hash);
		if (_5) {
			zephir_array_fetch_long(&_7, data, 0, PH_NOISY | PH_READONLY TSRMLS_CC);
			ZEPHIR_CALL_CE_STATIC(&_6, ouchbase__etc_ce, "getentityhash", &_0, _7);
			zephir_check_call_status();
			_5 = ZEPHIR_IS_IDENTICAL(_6, hash);
		}
		if (_5) {
			break;
		}
		_8 = zephir_fetch_nproperty_this(this_ptr, SL("em"), PH_NOISY_CC);
		zephir_array_fetch_long(&_9, data, 0, PH_NOISY | PH_READONLY TSRMLS_CC);
		ZEPHIR_CALL_METHOD(&repository, _8, "getrepository", NULL, _9);
		zephir_check_call_status();
		_10 = zephir_fetch_nproperty_this(this_ptr, SL("em"), PH_NOISY_CC);
		ZEPHIR_CALL_METHOD(&_11, _10, "getconnection",  NULL);
		zephir_check_call_status();
		zephir_array_fetch_long(&_13, data, 0, PH_NOISY | PH_READONLY TSRMLS_CC);
		ZEPHIR_CALL_METHOD(&_14, _13, "getid",  NULL);
		zephir_check_call_status();
		ZEPHIR_CALL_METHOD(&_12, repository, "getkey", NULL, _14);
		zephir_check_call_status();
		zephir_array_fetch_long(&_16, data, 0, PH_NOISY | PH_READONLY TSRMLS_CC);
		ZEPHIR_CALL_METHOD(&_15, im, "getoriginaldata", &_17, _16);
		zephir_check_call_status();
		ZEPHIR_CALL_METHOD(NULL, _11, "set", NULL, _12, _15);
		zephir_check_call_status();
	}
	RETURN_THIS();

}

/**
 * @return this
 */
PHP_METHOD(Ouchbase_UnitOfWork, clear) {

	zval *_0, *_1, *_2;

	ZEPHIR_MM_GROW();

	ZEPHIR_INIT_VAR(_0);
	array_init(_0);
	zephir_update_property_this(this_ptr, SL("persisted"), _0 TSRMLS_CC);
	ZEPHIR_INIT_VAR(_1);
	array_init(_1);
	zephir_update_property_this(this_ptr, SL("deleted"), _1 TSRMLS_CC);
	ZEPHIR_INIT_VAR(_2);
	array_init(_2);
	zephir_update_property_this(this_ptr, SL("inserted"), _2 TSRMLS_CC);
	RETURN_THIS();

}

