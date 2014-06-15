
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
#include "kernel/hash.h"
#include "kernel/array.h"

ZEPHIR_INIT_CLASS(Ouchbase_EntityManager) {

	ZEPHIR_REGISTER_CLASS(Ouchbase, EntityManager, ouchbase, entitymanager, ouchbase_entitymanager_method_entry, 0);

	/**
	 * @var array
	 */
	zend_declare_property_null(ouchbase_entitymanager_ce, SL("entityRepositories"), ZEND_ACC_PROTECTED TSRMLS_CC);

	/**
	 * @var \Ouchbase\UnitOfWork
	 */
	zend_declare_property_null(ouchbase_entitymanager_ce, SL("uow"), ZEND_ACC_PROTECTED TSRMLS_CC);

	/**
	 * @var \Ouchbase\IdentityMap
	 */
	zend_declare_property_null(ouchbase_entitymanager_ce, SL("im"), ZEND_ACC_PROTECTED TSRMLS_CC);

	/**
	 * @var \Couchbase
	 */
	zend_declare_property_null(ouchbase_entitymanager_ce, SL("cb"), ZEND_ACC_PROTECTED TSRMLS_CC);

	/**
	 * @var \Ouchbase\Repository[]
	 */
	zend_declare_property_null(ouchbase_entitymanager_ce, SL("_repositories"), ZEND_ACC_PROTECTED TSRMLS_CC);

	return SUCCESS;

}

/**
 * @param \Couchbase couchbase
 */
PHP_METHOD(Ouchbase_EntityManager, __construct) {

	int ZEPHIR_LAST_CALL_STATUS;
	zval *couchbase, *_0, *_1, *_2, *_3, *_4;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &couchbase);



	if (!(zephir_is_instance_of(couchbase, SL("Couchbase") TSRMLS_CC))) {
		ZEPHIR_THROW_EXCEPTION_DEBUG_STR(spl_ce_InvalidArgumentException, "Parameter 'couchbase' must be an instance of 'Couchbase'", "", 0);
		return;
	}
	ZEPHIR_INIT_VAR(_0);
	object_init_ex(_0, ouchbase_identitymap_ce);
	ZEPHIR_CALL_METHOD(NULL, _0, "__construct", NULL);
	zephir_check_call_status();
	zephir_update_property_this(this_ptr, SL("im"), _0 TSRMLS_CC);
	ZEPHIR_INIT_VAR(_1);
	object_init_ex(_1, ouchbase_unitofwork_ce);
	_2 = zephir_fetch_nproperty_this(this_ptr, SL("im"), PH_NOISY_CC);
	ZEPHIR_CALL_METHOD(NULL, _1, "__construct", NULL, this_ptr, _2);
	zephir_check_call_status();
	zephir_update_property_this(this_ptr, SL("uow"), _1 TSRMLS_CC);
	zephir_update_property_this(this_ptr, SL("cb"), couchbase TSRMLS_CC);
	ZEPHIR_INIT_VAR(_3);
	array_init(_3);
	zephir_update_property_this(this_ptr, SL("entityRepositories"), _3 TSRMLS_CC);
	ZEPHIR_INIT_VAR(_4);
	array_init(_4);
	zephir_update_property_this(this_ptr, SL("_repositories"), _4 TSRMLS_CC);
	ZEPHIR_MM_RESTORE();

}

/**
 * @param string entityClassName
 * @param string entityRepositoryClassName
 * @return this
 */
PHP_METHOD(Ouchbase_EntityManager, registerManagedEntityClass) {

	zval *entityClassName_param = NULL, *entityRepositoryClassName_param = NULL;
	zval *entityClassName = NULL, *entityRepositoryClassName = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 2, 0, &entityClassName_param, &entityRepositoryClassName_param);

	zephir_get_strval(entityClassName, entityClassName_param);
	zephir_get_strval(entityRepositoryClassName, entityRepositoryClassName_param);


	zephir_update_property_array(this_ptr, SL("entityRepositories"), entityClassName, entityRepositoryClassName TSRMLS_CC);
	RETURN_THIS();

}

/**
 * @param array map (entity class name => entity repository class name)
 * @return this
 */
PHP_METHOD(Ouchbase_EntityManager, registerManagedEntityClasses) {

	HashTable *_1;
	HashPosition _0;
	zval *map, *entityClassName = NULL, *entityRepositoryClassName = NULL, **_2;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &map);



	zephir_is_iterable(map, &_1, &_0, 0, 0);
	for (
	  ; zephir_hash_get_current_data_ex(_1, (void**) &_2, &_0) == SUCCESS
	  ; zephir_hash_move_forward_ex(_1, &_0)
	) {
		ZEPHIR_GET_HMKEY(entityClassName, _1, _0);
		ZEPHIR_GET_HVALUE(entityRepositoryClassName, _2);
		zephir_update_property_array(this_ptr, SL("entityRepositories"), entityClassName, entityRepositoryClassName TSRMLS_CC);
	}
	RETURN_THIS();

}

/**
 * @param string|\Ouchbase\Entity entityClassName
 * @return \Ouchbase\Repository
 */
PHP_METHOD(Ouchbase_EntityManager, getRepository) {

	int ZEPHIR_LAST_CALL_STATUS;
	zephir_nts_static zephir_fcall_cache_entry *_1 = NULL, *_5 = NULL;
	zval *entityClassName = NULL, *_0 = NULL, *_2, *_3, _4, *_6, *_7;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &entityClassName);

	ZEPHIR_SEPARATE_PARAM(entityClassName);


	if (Z_TYPE_P(entityClassName) == IS_OBJECT) {
		ZEPHIR_CALL_CE_STATIC(&_0, ouchbase__etc_ce, "getentityclass", &_1, entityClassName);
		zephir_check_call_status();
		ZEPHIR_CPY_WRT(entityClassName, _0);
	}
	_2 = zephir_fetch_nproperty_this(this_ptr, SL("entityRepositories"), PH_NOISY_CC);
	if (!(zephir_array_isset(_2, entityClassName))) {
		ZEPHIR_INIT_VAR(_3);
		object_init_ex(_3, ouchbase_exception_entitymanagerexception_ce);
		ZEPHIR_SINIT_VAR(_4);
		ZVAL_STRING(&_4, "Repository for '%s' was not registered in the entity manager", 0);
		ZEPHIR_CALL_FUNCTION(&_0, "sprintf", &_5, &_4, entityClassName);
		zephir_check_call_status();
		ZEPHIR_CALL_METHOD(NULL, _3, "__construct", NULL, _0);
		zephir_check_call_status();
		zephir_throw_exception_debug(_3, "ouchbase/EntityManager.zep", 80 TSRMLS_CC);
		ZEPHIR_MM_RESTORE();
		return;
	}
	_6 = zephir_fetch_nproperty_this(this_ptr, SL("entityRepositories"), PH_NOISY_CC);
	zephir_array_fetch(&_7, _6, entityClassName, PH_NOISY | PH_READONLY TSRMLS_CC);
	ZEPHIR_RETURN_CALL_METHOD(this_ptr, "getcachedrepository", NULL, _7);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * @param string repositoryClassName
 * @return \Ouchbase\Repository
 */
PHP_METHOD(Ouchbase_EntityManager, getCachedRepository) {

	int ZEPHIR_LAST_CALL_STATUS;
	zend_class_entry *_2;
	zval *repositoryClassName_param = NULL, *_0, *_1, *_3, *_4, *_5, *_6;
	zval *repositoryClassName = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &repositoryClassName_param);

	zephir_get_strval(repositoryClassName, repositoryClassName_param);


	_0 = zephir_fetch_nproperty_this(this_ptr, SL("_repositories"), PH_NOISY_CC);
	if (!(zephir_array_isset(_0, repositoryClassName))) {
		ZEPHIR_INIT_VAR(_1);
		_2 = zend_fetch_class(Z_STRVAL_P(repositoryClassName), Z_STRLEN_P(repositoryClassName), ZEND_FETCH_CLASS_AUTO TSRMLS_CC);
		object_init_ex(_1, _2);
		if (zephir_has_constructor(_1 TSRMLS_CC)) {
			_3 = zephir_fetch_nproperty_this(this_ptr, SL("uow"), PH_NOISY_CC);
			_4 = zephir_fetch_nproperty_this(this_ptr, SL("im"), PH_NOISY_CC);
			_5 = zephir_fetch_nproperty_this(this_ptr, SL("cb"), PH_NOISY_CC);
			ZEPHIR_CALL_METHOD(NULL, _1, "__construct", NULL, _3, _4, _5);
			zephir_check_call_status();
		}
		zephir_update_property_array(this_ptr, SL("_repositories"), repositoryClassName, _1 TSRMLS_CC);
	}
	_3 = zephir_fetch_nproperty_this(this_ptr, SL("_repositories"), PH_NOISY_CC);
	zephir_array_fetch(&_6, _3, repositoryClassName, PH_NOISY | PH_READONLY TSRMLS_CC);
	RETURN_CTOR(_6);

}

/**
 * @param \Ouchbase\Entity entity
 * @return this
 */
PHP_METHOD(Ouchbase_EntityManager, persist) {

	zephir_nts_static zephir_fcall_cache_entry *_5 = NULL;
	int ZEPHIR_LAST_CALL_STATUS;
	zval *entity, *_0, *_1 = NULL, *_2, *_3 = NULL, *_4 = NULL, *_6 = NULL, *_7;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &entity);



	if (!(zephir_instance_of_ev(entity, ouchbase_entity_ce TSRMLS_CC))) {
		ZEPHIR_THROW_EXCEPTION_DEBUG_STR(spl_ce_InvalidArgumentException, "Parameter 'entity' must be an instance of 'Ouchbase\\Entity'", "", 0);
		return;
	}
	_0 = zephir_fetch_nproperty_this(this_ptr, SL("im"), PH_NOISY_CC);
	ZEPHIR_CALL_METHOD(&_1, _0, "contains", NULL, entity);
	zephir_check_call_status();
	if (zephir_is_true(_1)) {
		_2 = zephir_fetch_nproperty_this(this_ptr, SL("uow"), PH_NOISY_CC);
		ZEPHIR_CALL_METHOD(NULL, _2, "persist", NULL, entity);
		zephir_check_call_status();
	} else {
		_2 = zephir_fetch_nproperty_this(this_ptr, SL("im"), PH_NOISY_CC);
		ZEPHIR_CALL_CE_STATIC(&_4, ouchbase__etc_ce, "getentityclass", &_5, entity);
		zephir_check_call_status();
		ZEPHIR_CALL_METHOD(&_3, this_ptr, "getrepository", NULL, _4);
		zephir_check_call_status();
		ZEPHIR_CALL_METHOD(&_6, _3, "toarray", NULL, entity);
		zephir_check_call_status();
		ZEPHIR_CALL_METHOD(NULL, _2, "register", NULL, entity, _6);
		zephir_check_call_status();
		_7 = zephir_fetch_nproperty_this(this_ptr, SL("uow"), PH_NOISY_CC);
		ZEPHIR_CALL_METHOD(NULL, _7, "insert", NULL, entity);
		zephir_check_call_status();
	}
	RETURN_THIS();

}

/**
 * @param \Ouchbase\Entity entity
 * @return this
 */
PHP_METHOD(Ouchbase_EntityManager, delete) {

	int ZEPHIR_LAST_CALL_STATUS;
	zval *entity, *_0;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &entity);



	if (!(zephir_instance_of_ev(entity, ouchbase_entity_ce TSRMLS_CC))) {
		ZEPHIR_THROW_EXCEPTION_DEBUG_STR(spl_ce_InvalidArgumentException, "Parameter 'entity' must be an instance of 'Ouchbase\\Entity'", "", 0);
		return;
	}
	_0 = zephir_fetch_nproperty_this(this_ptr, SL("uow"), PH_NOISY_CC);
	ZEPHIR_CALL_METHOD(NULL, _0, "delete", NULL, entity);
	zephir_check_call_status();
	RETURN_THIS();

}

/**
 * @param \Ouchbase\Entity entity
 * @param bool concurrent If entity may have concurrent updates
 * @throws \LogicException
 * @return this
 */
PHP_METHOD(Ouchbase_EntityManager, refresh) {

	int ZEPHIR_LAST_CALL_STATUS;
	zephir_nts_static zephir_fcall_cache_entry *_2 = NULL;
	zend_bool concurrent;
	zval *entity, *concurrent_param = NULL, *_0 = NULL, *_1 = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 1, &entity, &concurrent_param);

	if (!concurrent_param) {
		concurrent = 0;
	} else {
		concurrent = zephir_get_boolval(concurrent_param);
	}


	if (!(zephir_instance_of_ev(entity, ouchbase_entity_ce TSRMLS_CC))) {
		ZEPHIR_THROW_EXCEPTION_DEBUG_STR(spl_ce_InvalidArgumentException, "Parameter 'entity' must be an instance of 'Ouchbase\\Entity'", "", 0);
		return;
	}
	ZEPHIR_CALL_CE_STATIC(&_1, ouchbase__etc_ce, "getentityclass", &_2, entity);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&_0, this_ptr, "getrepository", NULL, _1);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(NULL, _0, "refresh", NULL, entity, (concurrent ? ZEPHIR_GLOBAL(global_true) : ZEPHIR_GLOBAL(global_false)));
	zephir_check_call_status();
	RETURN_THIS();

}

/**
 * @return this
 */
PHP_METHOD(Ouchbase_EntityManager, flush) {

	int ZEPHIR_LAST_CALL_STATUS;
	zval *_0;

	ZEPHIR_MM_GROW();

	_0 = zephir_fetch_nproperty_this(this_ptr, SL("uow"), PH_NOISY_CC);
	ZEPHIR_CALL_METHOD(NULL, _0, "commit", NULL);
	zephir_check_call_status();
	RETURN_THIS();

}

/**
 * @return this
 */
PHP_METHOD(Ouchbase_EntityManager, clear) {

	int ZEPHIR_LAST_CALL_STATUS;
	zval *_0, *_1;

	ZEPHIR_MM_GROW();

	_0 = zephir_fetch_nproperty_this(this_ptr, SL("im"), PH_NOISY_CC);
	ZEPHIR_CALL_METHOD(NULL, _0, "clear", NULL);
	zephir_check_call_status();
	_1 = zephir_fetch_nproperty_this(this_ptr, SL("uow"), PH_NOISY_CC);
	ZEPHIR_CALL_METHOD(NULL, _1, "clear", NULL);
	zephir_check_call_status();
	RETURN_THIS();

}

/**
 * Swap / Apply callback to entity and save it "atomically"
 *
 * @param \Ouchbase\Entity entity
 * @param callable callback Accepts entity as argument and modifies it
 * @throws \Ouchbase\Exception\EntityUpdateFailedException
 * @return this
 */
PHP_METHOD(Ouchbase_EntityManager, update) {

	zephir_fcall_cache_entry *_1 = NULL;
	zephir_nts_static zephir_fcall_cache_entry *_0 = NULL, *_6 = NULL, *_7 = NULL, *_10 = NULL;
	zend_bool updated = 0, _8;
	int ZEPHIR_LAST_CALL_STATUS, attempts = 0;
	zval *entity = NULL, *callback, *args = NULL, *result = NULL, *e = NULL, *_2, _3 = zval_used_for_init, _4 = zval_used_for_init, *_5 = NULL, *_9;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 2, 0, &entity, &callback);

	ZEPHIR_SEPARATE_PARAM(entity);


	if (!(zephir_instance_of_ev(entity, ouchbase_entity_ce TSRMLS_CC))) {
		ZEPHIR_THROW_EXCEPTION_DEBUG_STR(spl_ce_InvalidArgumentException, "Parameter 'entity' must be an instance of 'Ouchbase\\Entity'", "", 0);
		return;
	}
	if (zephir_instance_of_ev(entity, ouchbase_entityproxy_ce TSRMLS_CC)) {
		ZEPHIR_CALL_METHOD(&entity, entity, "_getobject",  NULL);
		zephir_check_call_status();
	}
	ZEPHIR_CALL_FUNCTION(&args, "func_get_args", &_0);
	zephir_check_call_status();
	zephir_array_unset_long(&args, 1, PH_SEPARATE);
	while (1) {
		attempts += 1;
		ZEPHIR_CALL_METHOD(NULL, this_ptr, "refresh", &_1, entity, ZEPHIR_GLOBAL(global_true));
		zephir_check_call_status();
		ZEPHIR_INIT_NVAR(result);
		ZEPHIR_CALL_USER_FUNC_ARRAY(result, callback, args);
		zephir_check_call_status();

		/* try_start_1: */

			_2 = zephir_fetch_nproperty_this(this_ptr, SL("uow"), PH_NOISY_CC);
			ZEPHIR_CALL_METHOD(NULL, _2, "commit", NULL, entity);
			zephir_check_call_status_or_jump(try_end_1);
			RETURN_CCTOR(result);

		try_end_1:

		ZEPHIR_CPY_WRT(e, EG(exception));
		if (zephir_is_instance_of(e, SL("Ouchbase\\Exception\\EntityModifiedException") TSRMLS_CC)) {
			zend_clear_exception(TSRMLS_C);
			ZEPHIR_SINIT_NVAR(_3);
			ZVAL_LONG(&_3, 20);
			ZEPHIR_SINIT_NVAR(_4);
			ZVAL_LONG(&_4, 60);
			ZEPHIR_CALL_FUNCTION(&_5, "mt_rand", &_6, &_3, &_4);
			zephir_check_call_status();
			ZEPHIR_CALL_FUNCTION(NULL, "usleep", &_7, _5);
			zephir_check_call_status();
		}
		_8 = updated;
		if (!(_8)) {
			_8 = attempts > 20;
		}
		if (_8) {
			break;
		}
	}
	if (!(updated)) {
		ZEPHIR_INIT_VAR(_9);
		object_init_ex(_9, ouchbase_exception_entityupdatefailedexception_ce);
		ZEPHIR_SINIT_NVAR(_3);
		ZVAL_STRING(&_3, "Couldn't update entity in %d attempts", 0);
		ZEPHIR_SINIT_NVAR(_4);
		ZVAL_LONG(&_4, attempts);
		ZEPHIR_CALL_FUNCTION(&_5, "sprintf", &_10, &_3, &_4);
		zephir_check_call_status();
		ZEPHIR_CALL_METHOD(NULL, _9, "__construct", NULL, _5);
		zephir_check_call_status();
		zephir_throw_exception_debug(_9, "ouchbase/EntityManager.zep", 197 TSRMLS_CC);
		ZEPHIR_MM_RESTORE();
		return;
	}
	RETURN_CCTOR(result);

}

/**
 * @return \Couchbase
 */
PHP_METHOD(Ouchbase_EntityManager, getConnection) {


	RETURN_MEMBER(this_ptr, "cb");

}

