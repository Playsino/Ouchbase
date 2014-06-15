
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
#include "kernel/fcall.h"
#include "kernel/operators.h"
#include "kernel/array.h"
#include "kernel/string.h"
#include "kernel/hash.h"
#include "kernel/concat.h"


ZEPHIR_INIT_CLASS(Ouchbase_Repository) {

	ZEPHIR_REGISTER_CLASS(Ouchbase, Repository, ouchbase, repository, ouchbase_repository_method_entry, ZEND_ACC_EXPLICIT_ABSTRACT_CLASS);

	/**
	 * Override this property in subclasses
	 * @var string
	 */
	zend_declare_property_string(ouchbase_repository_ce, SL("keyPrefix"), "", ZEND_ACC_PROTECTED TSRMLS_CC);

	/**
	 * Override this property in subclasses
	 * @var string
	 */
	zend_declare_property_null(ouchbase_repository_ce, SL("className"), ZEND_ACC_PROTECTED TSRMLS_CC);

	/**
	 * @var \Ouchbase\UnitOfWork
	 */
	zend_declare_property_null(ouchbase_repository_ce, SL("uow"), ZEND_ACC_PRIVATE TSRMLS_CC);

	/**
	 * @var \Ouchbase\IdentityMap
	 */
	zend_declare_property_null(ouchbase_repository_ce, SL("im"), ZEND_ACC_PRIVATE TSRMLS_CC);

	/**
	 * @var \Couchbase
	 */
	zend_declare_property_null(ouchbase_repository_ce, SL("cb"), ZEND_ACC_PROTECTED TSRMLS_CC);

	/**
	 * @var \ReflectionClass
	 */
	zend_declare_property_null(ouchbase_repository_ce, SL("_classReflection"), ZEND_ACC_PROTECTED TSRMLS_CC);

	/**
	 * @var \ReflectionProperty[]
	 */
	zend_declare_property_null(ouchbase_repository_ce, SL("_propertyReflections"), ZEND_ACC_PROTECTED TSRMLS_CC);

	return SUCCESS;

}

/**
 * @param \Ouchbase\UnitOfWork unitOfWork
 * @param \Ouchbase\IdentityMap identityMap
 * @param \Couchbase couchbase
 */
PHP_METHOD(Ouchbase_Repository, __construct) {

	zval *unitOfWork, *identityMap, *couchbase, *_0;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 3, 0, &unitOfWork, &identityMap, &couchbase);



	if (!(zephir_instance_of_ev(unitOfWork, ouchbase_unitofwork_ce TSRMLS_CC))) {
		ZEPHIR_THROW_EXCEPTION_DEBUG_STR(spl_ce_InvalidArgumentException, "Parameter 'unitOfWork' must be an instance of 'Ouchbase\\UnitOfWork'", "", 0);
		return;
	}
	if (!(zephir_instance_of_ev(identityMap, ouchbase_identitymap_ce TSRMLS_CC))) {
		ZEPHIR_THROW_EXCEPTION_DEBUG_STR(spl_ce_InvalidArgumentException, "Parameter 'identityMap' must be an instance of 'Ouchbase\\IdentityMap'", "", 0);
		return;
	}
	if (!(zephir_is_instance_of(couchbase, SL("Couchbase") TSRMLS_CC))) {
		ZEPHIR_THROW_EXCEPTION_DEBUG_STR(spl_ce_InvalidArgumentException, "Parameter 'couchbase' must be an instance of 'Couchbase'", "", 0);
		return;
	}
	zephir_update_property_this(this_ptr, SL("uow"), unitOfWork TSRMLS_CC);
	zephir_update_property_this(this_ptr, SL("im"), identityMap TSRMLS_CC);
	zephir_update_property_this(this_ptr, SL("cb"), couchbase TSRMLS_CC);
	ZEPHIR_INIT_VAR(_0);
	array_init(_0);
	zephir_update_property_this(this_ptr, SL("_propertyReflections"), _0 TSRMLS_CC);
	ZEPHIR_MM_RESTORE();

}

/**
 * @param int|string id
 * @param bool concurrent
 * @return \Ouchbase\Entity|null
 */
PHP_METHOD(Ouchbase_Repository, find) {

	zval *_2;
	int ZEPHIR_LAST_CALL_STATUS;
	zend_bool concurrent;
	zval *id, *concurrent_param = NULL, *entity = NULL, *_0, *_1, *cas, *data = NULL, *dataWithCas = NULL, *_3, *_4, *_5, *_6 = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 1, &id, &concurrent_param);

	if (!concurrent_param) {
		concurrent = 0;
	} else {
		concurrent = zephir_get_boolval(concurrent_param);
	}


	_0 = zephir_fetch_nproperty_this(this_ptr, SL("im"), PH_NOISY_CC);
	_1 = zephir_fetch_nproperty_this(this_ptr, SL("className"), PH_NOISY_CC);
	ZEPHIR_CALL_METHOD(&entity, _0, "getentity", NULL, _1, id);
	zephir_check_call_status();
	if (zephir_is_true(entity)) {
		RETURN_CCTOR(entity);
	}
	ZEPHIR_INIT_VAR(_2);
	array_init_size(_2, 2);
	zephir_array_fast_append(_2, id);
	ZEPHIR_INIT_VAR(_3);
	ZVAL_STRING(_3, "__getWithCas", 0);
	ZEPHIR_CALL_METHOD(&dataWithCas, this_ptr, "executewithouttimeouts", NULL, _3, _2);
	zephir_check_temp_parameter(_3);
	zephir_check_call_status();
	ZEPHIR_OBS_VAR(data);
	zephir_array_fetch_string(&data, dataWithCas, SL("data"), PH_NOISY TSRMLS_CC);
	ZEPHIR_OBS_VAR(cas);
	zephir_array_fetch_string(&cas, dataWithCas, SL("cas"), PH_NOISY TSRMLS_CC);
	if (!(zephir_is_true(data))) {
		RETURN_MM_NULL();
	}
	if (!(Z_TYPE_P(data) == IS_ARRAY)) {
		ZEPHIR_INIT_BNVAR(_3);
		zephir_json_decode(_3, &(_3), data, zephir_get_intval(ZEPHIR_GLOBAL(global_true))  TSRMLS_CC);
		ZEPHIR_CPY_WRT(data, _3);
	}
	ZEPHIR_CALL_METHOD(&entity, this_ptr, "toobject", NULL, data);
	zephir_check_call_status();
	_4 = zephir_fetch_nproperty_this(this_ptr, SL("im"), PH_NOISY_CC);
	ZEPHIR_CALL_METHOD(NULL, _4, "register", NULL, entity, data);
	zephir_check_call_status();
	_5 = zephir_fetch_nproperty_this(this_ptr, SL("uow"), PH_NOISY_CC);
	ZEPHIR_INIT_VAR(_6);
	if (concurrent) {
		ZEPHIR_CPY_WRT(_6, cas);
	} else {
		ZEPHIR_INIT_BNVAR(_6);
		ZVAL_NULL(_6);
	}
	ZEPHIR_CALL_METHOD(NULL, _5, "persist", NULL, entity, _6);
	zephir_check_call_status();
	RETURN_CCTOR(entity);

}

/**
 * @param \Ouchbase\Entity entity
 * @param bool concurrent If entity may have concurrent updates
 * @throws \Ouchbase\Exception\EntityLogicException
 * @return this
 */
PHP_METHOD(Ouchbase_Repository, refresh) {

	zephir_fcall_cache_entry *_12 = NULL, *_14 = NULL, *_15 = NULL;
	HashTable *_9;
	HashPosition _8;
	zval *_4;
	int ZEPHIR_LAST_CALL_STATUS;
	zend_bool concurrent;
	zval *entity = NULL, *concurrent_param = NULL, *_0, *_1 = NULL, *_2, *_3 = NULL, *cas, *data = NULL, *dataWithCas = NULL, *_5 = NULL, *refreshed = NULL, *_6, *property = NULL, *propertyReflection = NULL, *_7 = NULL, **_10, *_11 = NULL, *_13 = NULL, *_16;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 1, &entity, &concurrent_param);

	ZEPHIR_SEPARATE_PARAM(entity);
	if (!concurrent_param) {
		concurrent = 0;
	} else {
		concurrent = zephir_get_boolval(concurrent_param);
	}


	if (!(zephir_instance_of_ev(entity, ouchbase_entity_ce TSRMLS_CC))) {
		ZEPHIR_THROW_EXCEPTION_DEBUG_STR(spl_ce_InvalidArgumentException, "Parameter 'entity' must be an instance of 'Ouchbase\\Entity'", "", 0);
		return;
	}
	_0 = zephir_fetch_nproperty_this(this_ptr, SL("im"), PH_NOISY_CC);
	ZEPHIR_CALL_METHOD(&_1, _0, "contains", NULL, entity);
	zephir_check_call_status();
	if (!(zephir_is_true(_1))) {
		ZEPHIR_INIT_VAR(_2);
		object_init_ex(_2, ouchbase_exception_entitylogicexception_ce);
		ZEPHIR_INIT_VAR(_3);
		ZVAL_STRING(_3, "was not persisted", 0);
		ZEPHIR_CALL_METHOD(NULL, _2, "__construct", NULL, entity, _3);
		zephir_check_temp_parameter(_3);
		zephir_check_call_status();
		zephir_throw_exception_debug(_2, "ouchbase/Repository.zep", 97 TSRMLS_CC);
		ZEPHIR_MM_RESTORE();
		return;
	}
	if (zephir_instance_of_ev(entity, ouchbase_entityproxy_ce TSRMLS_CC)) {
		ZEPHIR_CALL_METHOD(&entity, entity, "_getobject",  NULL);
		zephir_check_call_status();
	}
	ZEPHIR_INIT_VAR(_4);
	array_init_size(_4, 2);
	ZEPHIR_CALL_METHOD(&_5, entity, "getid",  NULL);
	zephir_check_call_status();
	zephir_array_fast_append(_4, _5);
	ZEPHIR_INIT_NVAR(_3);
	ZVAL_STRING(_3, "__getWithCas", 0);
	ZEPHIR_CALL_METHOD(&dataWithCas, this_ptr, "executewithouttimeouts", NULL, _3, _4);
	zephir_check_temp_parameter(_3);
	zephir_check_call_status();
	ZEPHIR_OBS_VAR(data);
	zephir_array_fetch_string(&data, dataWithCas, SL("data"), PH_NOISY TSRMLS_CC);
	ZEPHIR_OBS_VAR(cas);
	zephir_array_fetch_string(&cas, dataWithCas, SL("cas"), PH_NOISY TSRMLS_CC);
	if (!(zephir_is_true(data))) {
		RETURN_THIS();
	}
	if (!(Z_TYPE_P(data) == IS_ARRAY)) {
		ZEPHIR_INIT_NVAR(_3);
		zephir_json_decode(_3, &(_3), data, zephir_get_intval(ZEPHIR_GLOBAL(global_true))  TSRMLS_CC);
		ZEPHIR_CPY_WRT(data, _3);
	}
	ZEPHIR_CALL_METHOD(&refreshed, this_ptr, "toobject", NULL, data);
	zephir_check_call_status();
	_6 = zephir_fetch_nproperty_this(this_ptr, SL("im"), PH_NOISY_CC);
	ZEPHIR_CALL_METHOD(NULL, _6, "updateoriginaldata", NULL, entity, data);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&_5, this_ptr, "getclassreflection",  NULL);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&_7, _5, "getproperties",  NULL);
	zephir_check_call_status();
	zephir_is_iterable(_7, &_9, &_8, 0, 0);
	for (
	  ; zephir_hash_get_current_data_ex(_9, (void**) &_10, &_8) == SUCCESS
	  ; zephir_hash_move_forward_ex(_9, &_8)
	) {
		ZEPHIR_GET_HVALUE(property, _10);
		ZEPHIR_CALL_METHOD(&_11, property, "getname",  NULL);
		zephir_check_call_status();
		ZEPHIR_CALL_METHOD(&propertyReflection, this_ptr, "getpropertyreflection", &_12, _11);
		zephir_check_call_status();
		ZEPHIR_CALL_METHOD(&_13, propertyReflection, "getvalue", &_14, refreshed);
		zephir_check_call_status();
		ZEPHIR_CALL_METHOD(NULL, propertyReflection, "setvalue", &_15, entity, _13);
		zephir_check_call_status();
	}
	if (concurrent) {
		_16 = zephir_fetch_nproperty_this(this_ptr, SL("uow"), PH_NOISY_CC);
		ZEPHIR_CALL_METHOD(NULL, _16, "persist", NULL, entity, cas);
		zephir_check_call_status();
	}
	RETURN_THIS();

}

/**
 * @param array ids
 * @param bool concurrent Only for entities fetched in this query
 * @return \Ouchbase\Entity[]
 */
PHP_METHOD(Ouchbase_Repository, findAll) {

	zephir_fcall_cache_entry *_7 = NULL;
	HashTable *_3;
	HashPosition _2;
	int ZEPHIR_LAST_CALL_STATUS;
	zval *_0;
	zend_bool concurrent;
	zval *ids, *concurrent_param = NULL, *entity = NULL, *entities, *cas, *data, *dataWithCas = NULL, *id = NULL, *entityData = NULL, *_1 = NULL, **_4, *_5, *_6, *_8, *_9, *_10 = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 1, &ids, &concurrent_param);

	if (!concurrent_param) {
		concurrent = 0;
	} else {
		concurrent = zephir_get_boolval(concurrent_param);
	}


	ZEPHIR_INIT_VAR(entities);
	array_init(entities);
	ZEPHIR_INIT_VAR(_0);
	array_init_size(_0, 2);
	zephir_array_fast_append(_0, ids);
	ZEPHIR_INIT_VAR(_1);
	ZVAL_STRING(_1, "__getMultiWithCas", 0);
	ZEPHIR_CALL_METHOD(&dataWithCas, this_ptr, "executewithouttimeouts", NULL, _1, _0);
	zephir_check_temp_parameter(_1);
	zephir_check_call_status();
	ZEPHIR_OBS_VAR(data);
	zephir_array_fetch_string(&data, dataWithCas, SL("data"), PH_NOISY TSRMLS_CC);
	ZEPHIR_OBS_VAR(cas);
	zephir_array_fetch_string(&cas, dataWithCas, SL("cas"), PH_NOISY TSRMLS_CC);
	zephir_is_iterable(data, &_3, &_2, 0, 0);
	for (
	  ; zephir_hash_get_current_data_ex(_3, (void**) &_4, &_2) == SUCCESS
	  ; zephir_hash_move_forward_ex(_3, &_2)
	) {
		ZEPHIR_GET_HMKEY(id, _3, _2);
		ZEPHIR_GET_HVALUE(entityData, _4);
		_5 = zephir_fetch_nproperty_this(this_ptr, SL("im"), PH_NOISY_CC);
		_6 = zephir_fetch_nproperty_this(this_ptr, SL("className"), PH_NOISY_CC);
		ZEPHIR_CALL_METHOD(&entity, _5, "getentity", NULL, _6, id);
		zephir_check_call_status();
		if (zephir_is_true(entity)) {
			zephir_array_append(&entities, entity, PH_SEPARATE);
			continue;
		}
		if (!(Z_TYPE_P(entityData) == IS_ARRAY)) {
			ZEPHIR_INIT_NVAR(_1);
			zephir_json_decode(_1, &(_1), entityData, zephir_get_intval(ZEPHIR_GLOBAL(global_true))  TSRMLS_CC);
			ZEPHIR_CPY_WRT(entityData, _1);
		}
		ZEPHIR_CALL_METHOD(&entity, this_ptr, "toobject", &_7, entityData);
		zephir_check_call_status();
		_8 = zephir_fetch_nproperty_this(this_ptr, SL("im"), PH_NOISY_CC);
		ZEPHIR_CALL_METHOD(NULL, _8, "register", NULL, entity, entityData);
		zephir_check_call_status();
		_9 = zephir_fetch_nproperty_this(this_ptr, SL("uow"), PH_NOISY_CC);
		ZEPHIR_INIT_LNVAR(_10);
		if (concurrent) {
			ZEPHIR_OBS_NVAR(_10);
			zephir_array_fetch(&_10, cas, id, PH_NOISY TSRMLS_CC);
		} else {
			ZEPHIR_INIT_NVAR(_10);
			ZVAL_NULL(_10);
		}
		ZEPHIR_CALL_METHOD(NULL, _9, "persist", NULL, entity, _10);
		zephir_check_call_status();
		zephir_array_append(&entities, entity, PH_SEPARATE);
	}
	RETURN_CCTOR(entities);

}

/**
 * @param \Ouchbase\Entity entity
 * @return this
 */
PHP_METHOD(Ouchbase_Repository, insert) {

	zval *_0;
	int ZEPHIR_LAST_CALL_STATUS;
	zval *entity, *data = NULL, *_1 = NULL, *_2 = NULL, *_3, *_4, *_5;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &entity);



	if (!(zephir_instance_of_ev(entity, ouchbase_entity_ce TSRMLS_CC))) {
		ZEPHIR_THROW_EXCEPTION_DEBUG_STR(spl_ce_InvalidArgumentException, "Parameter 'entity' must be an instance of 'Ouchbase\\Entity'", "", 0);
		return;
	}
	ZEPHIR_CALL_METHOD(&data, this_ptr, "toarray", NULL, entity);
	zephir_check_call_status();
	ZEPHIR_INIT_VAR(_0);
	array_init_size(_0, 3);
	ZEPHIR_CALL_METHOD(&_2, entity, "getid",  NULL);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&_1, this_ptr, "getkey", NULL, _2);
	zephir_check_call_status();
	zephir_array_fast_append(_0, _1);
	ZEPHIR_INIT_VAR(_3);
	zephir_json_encode(_3, &(_3), data, 0  TSRMLS_CC);
	zephir_array_fast_append(_0, _3);
	ZEPHIR_INIT_BNVAR(_3);
	ZVAL_STRING(_3, "set", 0);
	ZEPHIR_CALL_METHOD(NULL, this_ptr, "executewithouttimeouts", NULL, _3, _0);
	zephir_check_temp_parameter(_3);
	zephir_check_call_status();
	_4 = zephir_fetch_nproperty_this(this_ptr, SL("uow"), PH_NOISY_CC);
	ZEPHIR_CALL_METHOD(NULL, _4, "persist", NULL, entity);
	zephir_check_call_status();
	_5 = zephir_fetch_nproperty_this(this_ptr, SL("im"), PH_NOISY_CC);
	ZEPHIR_CALL_METHOD(NULL, _5, "updateoriginaldata", NULL, entity, data);
	zephir_check_call_status();
	RETURN_THIS();

}

/**
 * @todo cas argument is inconsistent here
 *
 * @param \Ouchbase\Entity entity
 * @param string|null cas
 * @throws \Ouchbase\Exception\EntityLogicException
 * @throws \Ouchbase\Exception\EntityModifiedException
 * @return this
 */
PHP_METHOD(Ouchbase_Repository, update) {

	zend_class_entry *_8;
	zval *_5 = NULL;
	int ZEPHIR_LAST_CALL_STATUS;
	zval *entity = NULL, *cas = NULL, *_0 = NULL, *data = NULL, *originalData = NULL, *_1, *_2 = NULL, *_3 = NULL, *_4, *_6 = NULL, *e = NULL, *_7 = NULL, *ex;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 1, &entity, &cas);

	ZEPHIR_SEPARATE_PARAM(entity);
	if (!cas) {
		cas = ZEPHIR_GLOBAL(global_null);
	}


	if (!(zephir_instance_of_ev(entity, ouchbase_entity_ce TSRMLS_CC))) {
		ZEPHIR_THROW_EXCEPTION_DEBUG_STR(spl_ce_InvalidArgumentException, "Parameter 'entity' must be an instance of 'Ouchbase\\Entity'", "", 0);
		return;
	}
	if (zephir_instance_of_ev(entity, ouchbase_entityproxy_ce TSRMLS_CC)) {
		ZEPHIR_CALL_METHOD(&_0, entity, "isproxied",  NULL);
		zephir_check_call_status();
		if (!(zephir_is_true(_0))) {
			RETURN_THIS();
		}
		ZEPHIR_CALL_METHOD(&entity, entity, "_getobject",  NULL);
		zephir_check_call_status();
	}
	ZEPHIR_CALL_METHOD(&data, this_ptr, "toarray", NULL, entity);
	zephir_check_call_status();
	_1 = zephir_fetch_nproperty_this(this_ptr, SL("im"), PH_NOISY_CC);
	ZEPHIR_CALL_METHOD(&originalData, _1, "getoriginaldata", NULL, entity);
	zephir_check_call_status();
	if (!(zephir_is_true(originalData))) {
		ZEPHIR_INIT_VAR(_2);
		object_init_ex(_2, ouchbase_exception_entitylogicexception_ce);
		ZEPHIR_INIT_VAR(_3);
		ZVAL_STRING(_3, "was not registered in the identity map", 0);
		ZEPHIR_CALL_METHOD(NULL, _2, "__construct", NULL, entity, _3);
		zephir_check_temp_parameter(_3);
		zephir_check_call_status();
		zephir_throw_exception_debug(_2, "ouchbase/Repository.zep", 215 TSRMLS_CC);
		ZEPHIR_MM_RESTORE();
		return;
	}
	if (ZEPHIR_IS_EQUAL(data, originalData)) {
		RETURN_THIS();
	}
	_4 = zephir_fetch_nproperty_this(this_ptr, SL("im"), PH_NOISY_CC);
	ZEPHIR_CALL_METHOD(NULL, _4, "updateoriginaldata", NULL, entity, data);
	zephir_check_call_status();
	if (!(zephir_is_true(cas))) {
		ZEPHIR_INIT_VAR(_5);
		array_init_size(_5, 3);
		ZEPHIR_CALL_METHOD(&_6, entity, "getid",  NULL);
		zephir_check_call_status();
		ZEPHIR_CALL_METHOD(&_0, this_ptr, "getkey", NULL, _6);
		zephir_check_call_status();
		zephir_array_fast_append(_5, _0);
		ZEPHIR_INIT_NVAR(_3);
		zephir_json_encode(_3, &(_3), data, 0  TSRMLS_CC);
		zephir_array_fast_append(_5, _3);
		ZEPHIR_INIT_NVAR(_3);
		ZVAL_STRING(_3, "replace", 0);
		ZEPHIR_CALL_METHOD(NULL, this_ptr, "executewithouttimeouts", NULL, _3, _5);
		zephir_check_temp_parameter(_3);
		zephir_check_call_status();
		RETURN_THIS();
	}

	/* try_start_1: */

		ZEPHIR_INIT_NVAR(_5);
		array_init_size(_5, 6);
		ZEPHIR_CALL_METHOD(&_7, entity, "getid",  NULL);
		zephir_check_call_status_or_jump(try_end_1);
		ZEPHIR_CALL_METHOD(&_6, this_ptr, "getkey", NULL, _7);
		zephir_check_call_status_or_jump(try_end_1);
		zephir_array_fast_append(_5, _6);
		ZEPHIR_INIT_NVAR(_3);
		zephir_json_encode(_3, &(_3), data, 0  TSRMLS_CC);
		zephir_array_fast_append(_5, _3);
		ZEPHIR_INIT_NVAR(_3);
		ZVAL_LONG(_3, 0);
		zephir_array_fast_append(_5, _3);
		zephir_array_fast_append(_5, cas);
		ZEPHIR_INIT_NVAR(_3);
		ZVAL_STRING(_3, "replace", 0);
		ZEPHIR_CALL_METHOD(&_0, this_ptr, "executewithouttimeouts", NULL, _3, _5);
		zephir_check_temp_parameter(_3);
		zephir_check_call_status_or_jump(try_end_1);
		if (!(zephir_is_true(_0))) {
			ZEPHIR_INIT_LNVAR(_2);
			_8 = zend_fetch_class(SL("CouchbaseKeyMutatedException"), ZEND_FETCH_CLASS_AUTO TSRMLS_CC);
			object_init_ex(_2, _8);
			ZEPHIR_CALL_METHOD(NULL, _2, "__construct", NULL);
			zephir_check_call_status_or_jump(try_end_1);
			zephir_throw_exception_debug(_2, "ouchbase/Repository.zep", 233 TSRMLS_CC);
			goto try_end_1;

		}
		RETURN_THIS();

	try_end_1:

	ZEPHIR_CPY_WRT(e, EG(exception));
	if (zephir_is_instance_of(e, SL("CouchbaseKeyMutatedException") TSRMLS_CC)) {
		zend_clear_exception(TSRMLS_C);
		ZEPHIR_INIT_VAR(ex);
		object_init_ex(ex, ouchbase_exception_entitymodifiedexception_ce);
		ZEPHIR_INIT_NVAR(_3);
		ZVAL_STRING(_3, "was modified", 0);
		ZEPHIR_CALL_METHOD(NULL, ex, "__construct", NULL, entity, _3);
		zephir_check_temp_parameter(_3);
		zephir_check_call_status();
		ZEPHIR_INIT_NVAR(_3);
		ZVAL_STRING(_3, "update", 0);
		ZEPHIR_CALL_METHOD(NULL, ex, "setaction", NULL, _3);
		zephir_check_temp_parameter(_3);
		zephir_check_call_status();
		zephir_throw_exception_debug(ex, "ouchbase/Repository.zep", 242 TSRMLS_CC);
		ZEPHIR_MM_RESTORE();
		return;
	}
	RETURN_THIS();

}

/**
 * @todo cas argument is inconsistent here
 *
 * @param \Ouchbase\Entity entity
 * @param string|null cas
 * @throws \Ouchbase\Exception\EntityModifiedException
 * @return this
 */
PHP_METHOD(Ouchbase_Repository, delete) {

	int ZEPHIR_LAST_CALL_STATUS;
	zval *_0 = NULL;
	zval *entity, *cas = NULL, *_1 = NULL, *_2 = NULL, *_3 = NULL, *_4, *e = NULL, *ex;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 1, &entity, &cas);

	if (!cas) {
		cas = ZEPHIR_GLOBAL(global_null);
	}


	if (!(zephir_instance_of_ev(entity, ouchbase_entity_ce TSRMLS_CC))) {
		ZEPHIR_THROW_EXCEPTION_DEBUG_STR(spl_ce_InvalidArgumentException, "Parameter 'entity' must be an instance of 'Ouchbase\\Entity'", "", 0);
		return;
	}
	if (!(zephir_is_true(cas))) {
		ZEPHIR_INIT_VAR(_0);
		array_init_size(_0, 2);
		ZEPHIR_CALL_METHOD(&_2, entity, "getid",  NULL);
		zephir_check_call_status();
		ZEPHIR_CALL_METHOD(&_1, this_ptr, "getkey", NULL, _2);
		zephir_check_call_status();
		zephir_array_fast_append(_0, _1);
		ZEPHIR_INIT_VAR(_3);
		ZVAL_STRING(_3, "delete", 0);
		ZEPHIR_CALL_METHOD(NULL, this_ptr, "executewithouttimeouts", NULL, _3, _0);
		zephir_check_temp_parameter(_3);
		zephir_check_call_status();
		_4 = zephir_fetch_nproperty_this(this_ptr, SL("im"), PH_NOISY_CC);
		ZEPHIR_CALL_METHOD(NULL, _4, "unregister", NULL, entity);
		zephir_check_call_status();
		RETURN_THIS();
	}

	/* try_start_1: */

		ZEPHIR_INIT_NVAR(_0);
		array_init_size(_0, 3);
		ZEPHIR_CALL_METHOD(&_2, entity, "getid",  NULL);
		zephir_check_call_status_or_jump(try_end_1);
		ZEPHIR_CALL_METHOD(&_1, this_ptr, "getkey", NULL, _2);
		zephir_check_call_status_or_jump(try_end_1);
		zephir_array_fast_append(_0, _1);
		zephir_array_fast_append(_0, cas);
		ZEPHIR_INIT_NVAR(_3);
		ZVAL_STRING(_3, "delete", 0);
		ZEPHIR_CALL_METHOD(NULL, this_ptr, "executewithouttimeouts", NULL, _3, _0);
		zephir_check_temp_parameter(_3);
		zephir_check_call_status_or_jump(try_end_1);
		_4 = zephir_fetch_nproperty_this(this_ptr, SL("im"), PH_NOISY_CC);
		ZEPHIR_CALL_METHOD(NULL, _4, "unregister", NULL, entity);
		zephir_check_call_status_or_jump(try_end_1);
		RETURN_THIS();

	try_end_1:

	ZEPHIR_CPY_WRT(e, EG(exception));
	if (zephir_is_instance_of(e, SL("CouchbaseKeyMutatedException") TSRMLS_CC)) {
		zend_clear_exception(TSRMLS_C);
		ZEPHIR_INIT_VAR(ex);
		object_init_ex(ex, ouchbase_exception_entitymodifiedexception_ce);
		ZEPHIR_INIT_NVAR(_3);
		ZVAL_STRING(_3, "was modified", 0);
		ZEPHIR_CALL_METHOD(NULL, ex, "__construct", NULL, entity, _3);
		zephir_check_temp_parameter(_3);
		zephir_check_call_status();
		ZEPHIR_INIT_NVAR(_3);
		ZVAL_STRING(_3, "delete", 0);
		ZEPHIR_CALL_METHOD(NULL, ex, "setaction", NULL, _3);
		zephir_check_temp_parameter(_3);
		zephir_check_call_status();
		zephir_throw_exception_debug(ex, "ouchbase/Repository.zep", 274 TSRMLS_CC);
		ZEPHIR_MM_RESTORE();
		return;
	}
	RETURN_THIS();

}

/**
 * Executes the callback/Couchbase command that may throw Couchbase timeout
 * and ensures that the callback/Couchbase command is performed without timeouts
 * in the given number of attempts
 *
 * Optionally if Couchbase command was passed can take Couchbase command arguments
 *
 * Passing callback is needed for Couchbase commands that take arguments by reference
 *
 * @param callable|string command Couchbase or class method
 * @param array args Command args (optional)
 * @throws \CouchbaseLibcouchbaseException
 * @return mixed
 */
PHP_METHOD(Ouchbase_Repository, executeWithoutTimeouts) {

	zend_bool _11;
	zephir_fcall_cache_entry *_10 = NULL;
	zend_class_entry *_9;
	zephir_nts_static zephir_fcall_cache_entry *_3 = NULL, *_12 = NULL, *_13 = NULL, *_18 = NULL;
	int attempts = 0, ZEPHIR_LAST_CALL_STATUS;
	zval *args = NULL, *_4 = NULL;
	zval *method_param = NULL, *args_param = NULL, *e = NULL, *result = NULL, _0 = zval_used_for_init, _1 = zval_used_for_init, *_2 = NULL, *_5 = NULL, *_6, *_7 = NULL, *_8 = NULL, *_14, *_15, *_16 = NULL, *_17 = NULL;
	zval *method = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 1, &method_param, &args_param);

	zephir_get_strval(method, method_param);
	if (!args_param) {
		ZEPHIR_INIT_VAR(args);
		array_init(args);
	} else {
		zephir_get_arrval(args, args_param);
	}


	while (1) {
		attempts = (attempts + 1);

		/* try_start_1: */

			ZEPHIR_SINIT_NVAR(_0);
			ZVAL_LONG(&_0, 0);
			ZEPHIR_SINIT_NVAR(_1);
			ZVAL_LONG(&_1, 2);
			ZEPHIR_CALL_FUNCTION(&_2, "substr", &_3, method, &_0, &_1);
			zephir_check_call_status_or_jump(try_end_1);
			if (!(ZEPHIR_IS_STRING(_2, "__"))) {
				ZEPHIR_INIT_NVAR(result);
				ZEPHIR_INIT_NVAR(_4);
				array_init_size(_4, 3);
				ZEPHIR_OBS_NVAR(_5);
				zephir_read_property_this(&_5, this_ptr, SL("cb"), PH_NOISY_CC);
				zephir_array_fast_append(_4, _5);
				zephir_array_fast_append(_4, method);
				ZEPHIR_CALL_USER_FUNC_ARRAY(result, _4, args);
				zephir_check_call_status_or_jump(try_end_1);
				_6 = zephir_fetch_nproperty_this(this_ptr, SL("cb"), PH_NOISY_CC);
				ZEPHIR_CALL_METHOD(&_7, _6, "getresultcode",  NULL);
				zephir_check_call_status_or_jump(try_end_1);
				do {
					if (ZEPHIR_IS_LONG(_7, 0)) {
						RETURN_CCTOR(result);
					}
					if (ZEPHIR_IS_LONG(_7, 12)) {
						ZEPHIR_INIT_LNVAR(_8);
						_9 = zend_fetch_class(SL("CouchbaseKeyMutatedException"), ZEND_FETCH_CLASS_AUTO TSRMLS_CC);
						object_init_ex(_8, _9);
						ZEPHIR_CALL_METHOD(NULL, _8, "__construct", &_10);
						zephir_check_call_status_or_jump(try_end_1);
						zephir_throw_exception_debug(_8, "ouchbase/Repository.zep", 305 TSRMLS_CC);
						goto try_end_1;

					}
				} while(0);

			} else {
				ZEPHIR_INIT_NVAR(_4);
				array_init_size(_4, 3);
				zephir_array_fast_append(_4, this_ptr);
				zephir_array_fast_append(_4, method);
				ZEPHIR_CALL_USER_FUNC_ARRAY(return_value, _4, args);
				zephir_check_call_status_or_jump(try_end_1);
				RETURN_MM();
			}

		try_end_1:

		ZEPHIR_CPY_WRT(e, EG(exception));
		if (zephir_is_instance_of(e, SL("CouchbaseLibcouchbaseException") TSRMLS_CC)) {
			zend_clear_exception(TSRMLS_C);
			_11 = !(zephir_is_instance_of(e, SL("CouchbaseLibcouchbaseException") TSRMLS_CC));
			if (_11) {
				_11 = !(zephir_is_instance_of(e, SL("CouchbaseTimeoutException") TSRMLS_CC));
			}
			if (_11) {
				zephir_throw_exception_debug(e, "ouchbase/Repository.zep", 317 TSRMLS_CC);
				ZEPHIR_MM_RESTORE();
				return;
			}
		}
		if (attempts > 3) {
			break;
		}
		ZEPHIR_SINIT_NVAR(_0);
		ZVAL_LONG(&_0, 20);
		ZEPHIR_SINIT_NVAR(_1);
		ZVAL_LONG(&_1, 100);
		ZEPHIR_CALL_FUNCTION(&_2, "mt_rand", &_12, &_0, &_1);
		zephir_check_call_status();
		ZEPHIR_CALL_FUNCTION(NULL, "usleep", &_13, _2);
		zephir_check_call_status();
	}
	if (zephir_is_true(e)) {
		zephir_throw_exception_debug(e, "ouchbase/Repository.zep", 330 TSRMLS_CC);
		ZEPHIR_MM_RESTORE();
		return;
	} else {
		ZEPHIR_INIT_LNVAR(_8);
		object_init_ex(_8, ouchbase_exception_couchbaseexception_ce);
		ZEPHIR_INIT_VAR(_14);
		zephir_fast_join_str(_14, SL(", "), args TSRMLS_CC);
		_6 = zephir_fetch_nproperty_this(this_ptr, SL("cb"), PH_NOISY_CC);
		ZEPHIR_CALL_METHOD(&_7, _6, "getresultcode",  NULL);
		zephir_check_call_status();
		_15 = zephir_fetch_nproperty_this(this_ptr, SL("cb"), PH_NOISY_CC);
		ZEPHIR_CALL_METHOD(&_16, _15, "getresultmessage",  NULL);
		zephir_check_call_status();
		ZEPHIR_SINIT_NVAR(_0);
		ZVAL_STRING(&_0, "Could not perform %s(%s) with result code '%s' and message '%s'", 0);
		ZEPHIR_CALL_FUNCTION(&_17, "sprintf", &_18, &_0, method, _14, _7, _16);
		zephir_check_call_status();
		ZEPHIR_CALL_METHOD(NULL, _8, "__construct", NULL, _17);
		zephir_check_call_status();
		zephir_throw_exception_debug(_8, "ouchbase/Repository.zep", 339 TSRMLS_CC);
		ZEPHIR_MM_RESTORE();
		return;
	}

}

/**
 * @param int|string id
 * @return string
 */
PHP_METHOD(Ouchbase_Repository, getKey) {

	zval *id, *_0;

	zephir_fetch_params(0, 1, 0, &id);



	_0 = zephir_fetch_nproperty_this(this_ptr, SL("keyPrefix"), PH_NOISY_CC);
	ZEPHIR_CONCAT_VV(return_value, _0, id);
	return;

}

/**
 * @return \ReflectionClass
 */
PHP_METHOD(Ouchbase_Repository, getClassReflection) {

	int ZEPHIR_LAST_CALL_STATUS;
	zend_class_entry *_2;
	zval *_0, *_1, *_3;

	ZEPHIR_MM_GROW();

	_0 = zephir_fetch_nproperty_this(this_ptr, SL("_classReflection"), PH_NOISY_CC);
	if (!(zephir_is_true(_0))) {
		ZEPHIR_INIT_VAR(_1);
		_2 = zend_fetch_class(SL("ReflectionClass"), ZEND_FETCH_CLASS_AUTO TSRMLS_CC);
		object_init_ex(_1, _2);
		_3 = zephir_fetch_nproperty_this(this_ptr, SL("className"), PH_NOISY_CC);
		ZEPHIR_CALL_METHOD(NULL, _1, "__construct", NULL, _3);
		zephir_check_call_status();
		zephir_update_property_this(this_ptr, SL("_classReflection"), _1 TSRMLS_CC);
	}
	RETURN_MM_MEMBER(this_ptr, "_classReflection");

}

/**
 * @param string property
 * @return \ReflectionProperty
 */
PHP_METHOD(Ouchbase_Repository, getPropertyReflection) {

	int ZEPHIR_LAST_CALL_STATUS;
	zval *property_param = NULL, *_0, *reflection = NULL, *_1 = NULL, *_2, *_3;
	zval *property = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &property_param);

	zephir_get_strval(property, property_param);


	_0 = zephir_fetch_nproperty_this(this_ptr, SL("_propertyReflections"), PH_NOISY_CC);
	if (!(zephir_array_isset(_0, property))) {
		ZEPHIR_CALL_METHOD(&_1, this_ptr, "getclassreflection",  NULL);
		zephir_check_call_status();
		ZEPHIR_CALL_METHOD(&reflection, _1, "getproperty", NULL, property);
		zephir_check_call_status();
		ZEPHIR_CALL_METHOD(NULL, reflection, "setaccessible", NULL, ZEPHIR_GLOBAL(global_true));
		zephir_check_call_status();
		zephir_update_property_array(this_ptr, SL("_propertyReflections"), property, reflection TSRMLS_CC);
	}
	_2 = zephir_fetch_nproperty_this(this_ptr, SL("_propertyReflections"), PH_NOISY_CC);
	zephir_array_fetch(&_3, _2, property, PH_NOISY | PH_READONLY TSRMLS_CC);
	RETURN_CTOR(_3);

}

/**
 * @param int|string id
 * @return array [value, cas]
 */
PHP_METHOD(Ouchbase_Repository, __getWithCas) {

	int ZEPHIR_LAST_CALL_STATUS;
	zval *id, *cas, *data = NULL, *_0, *_1 = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &id);



	ZEPHIR_INIT_VAR(cas);
	ZVAL_NULL(cas);
	_0 = zephir_fetch_nproperty_this(this_ptr, SL("cb"), PH_NOISY_CC);
	ZEPHIR_CALL_METHOD(&_1, this_ptr, "getkey", NULL, id);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&data, _0, "get", NULL, _1, ZEPHIR_GLOBAL(global_null), cas);
	zephir_check_call_status();
	array_init_size(return_value, 3);
	zephir_array_update_string(&return_value, SL("data"), &data, PH_COPY | PH_SEPARATE);
	zephir_array_update_string(&return_value, SL("cas"), &cas, PH_COPY | PH_SEPARATE);
	RETURN_MM();

}

/**
 * @param array ids
 * @return array [value, cas]
 */
PHP_METHOD(Ouchbase_Repository, __getMultiWithCas) {

	zephir_fcall_cache_entry *_4 = NULL;
	int ZEPHIR_LAST_CALL_STATUS;
	HashTable *_1, *_7;
	HashPosition _0, _6;
	zval *ids, *idsToKeys, *keysToCas, *cas, *data = NULL, *id = NULL, **_2, *_3 = NULL, *_5, **_8, *_9, *_10 = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &ids);



	ZEPHIR_INIT_VAR(idsToKeys);
	array_init(idsToKeys);
	ZEPHIR_INIT_VAR(keysToCas);
	array_init(keysToCas);
	ZEPHIR_INIT_VAR(cas);
	array_init(cas);
	zephir_is_iterable(ids, &_1, &_0, 0, 0);
	for (
	  ; zephir_hash_get_current_data_ex(_1, (void**) &_2, &_0) == SUCCESS
	  ; zephir_hash_move_forward_ex(_1, &_0)
	) {
		ZEPHIR_GET_HVALUE(id, _2);
		ZEPHIR_CALL_METHOD(&_3, this_ptr, "getkey", &_4, id);
		zephir_check_call_status();
		zephir_array_update_zval(&idsToKeys, id, &_3, PH_COPY | PH_SEPARATE);
	}
	_5 = zephir_fetch_nproperty_this(this_ptr, SL("cb"), PH_NOISY_CC);
	ZEPHIR_CALL_METHOD(&data, _5, "getmulti", NULL, idsToKeys, keysToCas);
	zephir_check_call_status();
	zephir_is_iterable(ids, &_7, &_6, 0, 0);
	for (
	  ; zephir_hash_get_current_data_ex(_7, (void**) &_8, &_6) == SUCCESS
	  ; zephir_hash_move_forward_ex(_7, &_6)
	) {
		ZEPHIR_GET_HVALUE(id, _8);
		ZEPHIR_OBS_NVAR(_10);
		zephir_array_fetch(&_10, idsToKeys, id, PH_NOISY TSRMLS_CC);
		zephir_array_fetch(&_9, keysToCas, _10, PH_NOISY | PH_READONLY TSRMLS_CC);
		zephir_array_update_zval(&cas, id, &_9, PH_COPY | PH_SEPARATE);
	}
	array_init_size(return_value, 3);
	zephir_array_update_string(&return_value, SL("data"), &data, PH_COPY | PH_SEPARATE);
	zephir_array_update_string(&return_value, SL("cas"), &cas, PH_COPY | PH_SEPARATE);
	RETURN_MM();

}

PHP_METHOD(Ouchbase_Repository, toArray) {

}

PHP_METHOD(Ouchbase_Repository, toObject) {

}

