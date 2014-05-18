
extern zend_class_entry *ouchbase_unitofwork_ce;

ZEPHIR_INIT_CLASS(Ouchbase_UnitOfWork);

PHP_METHOD(Ouchbase_UnitOfWork, __construct);
PHP_METHOD(Ouchbase_UnitOfWork, persist);
PHP_METHOD(Ouchbase_UnitOfWork, delete);
PHP_METHOD(Ouchbase_UnitOfWork, insert);
PHP_METHOD(Ouchbase_UnitOfWork, commit);
PHP_METHOD(Ouchbase_UnitOfWork, commitInserts);
PHP_METHOD(Ouchbase_UnitOfWork, commitDeletes);
PHP_METHOD(Ouchbase_UnitOfWork, commitUpdates);
PHP_METHOD(Ouchbase_UnitOfWork, rollbackUpdates);
PHP_METHOD(Ouchbase_UnitOfWork, rollbackDeletes);
PHP_METHOD(Ouchbase_UnitOfWork, clear);

ZEND_BEGIN_ARG_INFO_EX(arginfo_ouchbase_unitofwork___construct, 0, 0, 2)
	ZEND_ARG_INFO(0, entityManager)
	ZEND_ARG_INFO(0, identityMap)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_ouchbase_unitofwork_persist, 0, 0, 1)
	ZEND_ARG_INFO(0, entity)
	ZEND_ARG_INFO(0, cas)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_ouchbase_unitofwork_delete, 0, 0, 1)
	ZEND_ARG_INFO(0, entity)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_ouchbase_unitofwork_insert, 0, 0, 1)
	ZEND_ARG_INFO(0, entity)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_ouchbase_unitofwork_commit, 0, 0, 0)
	ZEND_ARG_INFO(0, entity)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_ouchbase_unitofwork_commitinserts, 0, 0, 0)
	ZEND_ARG_INFO(0, entity)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_ouchbase_unitofwork_commitdeletes, 0, 0, 0)
	ZEND_ARG_INFO(0, entity)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_ouchbase_unitofwork_commitupdates, 0, 0, 0)
	ZEND_ARG_INFO(0, entity)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_ouchbase_unitofwork_rollbackupdates, 0, 0, 1)
	ZEND_ARG_INFO(0, im)
	ZEND_ARG_INFO(0, entity)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_ouchbase_unitofwork_rollbackdeletes, 0, 0, 2)
	ZEND_ARG_INFO(0, im)
	ZEND_ARG_INFO(0, entity)
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(ouchbase_unitofwork_method_entry) {
	PHP_ME(Ouchbase_UnitOfWork, __construct, arginfo_ouchbase_unitofwork___construct, ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)
	PHP_ME(Ouchbase_UnitOfWork, persist, arginfo_ouchbase_unitofwork_persist, ZEND_ACC_PUBLIC)
	PHP_ME(Ouchbase_UnitOfWork, delete, arginfo_ouchbase_unitofwork_delete, ZEND_ACC_PUBLIC)
	PHP_ME(Ouchbase_UnitOfWork, insert, arginfo_ouchbase_unitofwork_insert, ZEND_ACC_PUBLIC)
	PHP_ME(Ouchbase_UnitOfWork, commit, arginfo_ouchbase_unitofwork_commit, ZEND_ACC_PUBLIC)
	PHP_ME(Ouchbase_UnitOfWork, commitInserts, arginfo_ouchbase_unitofwork_commitinserts, ZEND_ACC_PRIVATE)
	PHP_ME(Ouchbase_UnitOfWork, commitDeletes, arginfo_ouchbase_unitofwork_commitdeletes, ZEND_ACC_PRIVATE)
	PHP_ME(Ouchbase_UnitOfWork, commitUpdates, arginfo_ouchbase_unitofwork_commitupdates, ZEND_ACC_PRIVATE)
	PHP_ME(Ouchbase_UnitOfWork, rollbackUpdates, arginfo_ouchbase_unitofwork_rollbackupdates, ZEND_ACC_PRIVATE)
	PHP_ME(Ouchbase_UnitOfWork, rollbackDeletes, arginfo_ouchbase_unitofwork_rollbackdeletes, ZEND_ACC_PRIVATE)
	PHP_ME(Ouchbase_UnitOfWork, clear, NULL, ZEND_ACC_PUBLIC)
  PHP_FE_END
};
