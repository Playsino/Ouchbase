
extern zend_class_entry *ouchbase_entitymanager_ce;

ZEPHIR_INIT_CLASS(Ouchbase_EntityManager);

PHP_METHOD(Ouchbase_EntityManager, __construct);
PHP_METHOD(Ouchbase_EntityManager, registerManagedEntityClass);
PHP_METHOD(Ouchbase_EntityManager, registerManagedEntityClasses);
PHP_METHOD(Ouchbase_EntityManager, getRepository);
PHP_METHOD(Ouchbase_EntityManager, getCachedRepository);
PHP_METHOD(Ouchbase_EntityManager, persist);
PHP_METHOD(Ouchbase_EntityManager, delete);
PHP_METHOD(Ouchbase_EntityManager, refresh);
PHP_METHOD(Ouchbase_EntityManager, flush);
PHP_METHOD(Ouchbase_EntityManager, clear);
PHP_METHOD(Ouchbase_EntityManager, update);
PHP_METHOD(Ouchbase_EntityManager, getConnection);

ZEND_BEGIN_ARG_INFO_EX(arginfo_ouchbase_entitymanager___construct, 0, 0, 1)
	ZEND_ARG_INFO(0, couchbase)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_ouchbase_entitymanager_registermanagedentityclass, 0, 0, 2)
	ZEND_ARG_INFO(0, entityClassName)
	ZEND_ARG_INFO(0, entityRepositoryClassName)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_ouchbase_entitymanager_registermanagedentityclasses, 0, 0, 1)
	ZEND_ARG_INFO(0, map)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_ouchbase_entitymanager_getrepository, 0, 0, 1)
	ZEND_ARG_INFO(0, entityClassName)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_ouchbase_entitymanager_getcachedrepository, 0, 0, 1)
	ZEND_ARG_INFO(0, repositoryClassName)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_ouchbase_entitymanager_persist, 0, 0, 1)
	ZEND_ARG_INFO(0, entity)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_ouchbase_entitymanager_delete, 0, 0, 1)
	ZEND_ARG_INFO(0, entity)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_ouchbase_entitymanager_refresh, 0, 0, 1)
	ZEND_ARG_INFO(0, entity)
	ZEND_ARG_INFO(0, concurrent)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_ouchbase_entitymanager_update, 0, 0, 2)
	ZEND_ARG_INFO(0, entity)
	ZEND_ARG_INFO(0, callback)
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(ouchbase_entitymanager_method_entry) {
	PHP_ME(Ouchbase_EntityManager, __construct, arginfo_ouchbase_entitymanager___construct, ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)
	PHP_ME(Ouchbase_EntityManager, registerManagedEntityClass, arginfo_ouchbase_entitymanager_registermanagedentityclass, ZEND_ACC_PUBLIC)
	PHP_ME(Ouchbase_EntityManager, registerManagedEntityClasses, arginfo_ouchbase_entitymanager_registermanagedentityclasses, ZEND_ACC_PUBLIC)
	PHP_ME(Ouchbase_EntityManager, getRepository, arginfo_ouchbase_entitymanager_getrepository, ZEND_ACC_PUBLIC)
	PHP_ME(Ouchbase_EntityManager, getCachedRepository, arginfo_ouchbase_entitymanager_getcachedrepository, ZEND_ACC_PROTECTED)
	PHP_ME(Ouchbase_EntityManager, persist, arginfo_ouchbase_entitymanager_persist, ZEND_ACC_PUBLIC)
	PHP_ME(Ouchbase_EntityManager, delete, arginfo_ouchbase_entitymanager_delete, ZEND_ACC_PUBLIC)
	PHP_ME(Ouchbase_EntityManager, refresh, arginfo_ouchbase_entitymanager_refresh, ZEND_ACC_PUBLIC)
	PHP_ME(Ouchbase_EntityManager, flush, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Ouchbase_EntityManager, clear, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Ouchbase_EntityManager, update, arginfo_ouchbase_entitymanager_update, ZEND_ACC_PUBLIC)
	PHP_ME(Ouchbase_EntityManager, getConnection, NULL, ZEND_ACC_PUBLIC)
  PHP_FE_END
};
