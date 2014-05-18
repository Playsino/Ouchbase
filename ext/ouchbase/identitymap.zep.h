
extern zend_class_entry *ouchbase_identitymap_ce;

ZEPHIR_INIT_CLASS(Ouchbase_IdentityMap);

PHP_METHOD(Ouchbase_IdentityMap, __construct);
PHP_METHOD(Ouchbase_IdentityMap, register);
PHP_METHOD(Ouchbase_IdentityMap, unregister);
PHP_METHOD(Ouchbase_IdentityMap, contains);
PHP_METHOD(Ouchbase_IdentityMap, getEntity);
PHP_METHOD(Ouchbase_IdentityMap, getOriginalData);
PHP_METHOD(Ouchbase_IdentityMap, updateOriginalData);
PHP_METHOD(Ouchbase_IdentityMap, clear);

ZEND_BEGIN_ARG_INFO_EX(arginfo_ouchbase_identitymap_register, 0, 0, 2)
	ZEND_ARG_INFO(0, entity)
	ZEND_ARG_INFO(0, data)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_ouchbase_identitymap_unregister, 0, 0, 1)
	ZEND_ARG_INFO(0, entity)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_ouchbase_identitymap_contains, 0, 0, 1)
	ZEND_ARG_INFO(0, entity)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_ouchbase_identitymap_getentity, 0, 0, 2)
	ZEND_ARG_INFO(0, className)
	ZEND_ARG_INFO(0, id)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_ouchbase_identitymap_getoriginaldata, 0, 0, 1)
	ZEND_ARG_INFO(0, entity)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_ouchbase_identitymap_updateoriginaldata, 0, 0, 2)
	ZEND_ARG_INFO(0, entity)
	ZEND_ARG_INFO(0, data)
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(ouchbase_identitymap_method_entry) {
	PHP_ME(Ouchbase_IdentityMap, __construct, NULL, ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)
	PHP_ME(Ouchbase_IdentityMap, register, arginfo_ouchbase_identitymap_register, ZEND_ACC_PUBLIC)
	PHP_ME(Ouchbase_IdentityMap, unregister, arginfo_ouchbase_identitymap_unregister, ZEND_ACC_PUBLIC)
	PHP_ME(Ouchbase_IdentityMap, contains, arginfo_ouchbase_identitymap_contains, ZEND_ACC_PUBLIC)
	PHP_ME(Ouchbase_IdentityMap, getEntity, arginfo_ouchbase_identitymap_getentity, ZEND_ACC_PUBLIC)
	PHP_ME(Ouchbase_IdentityMap, getOriginalData, arginfo_ouchbase_identitymap_getoriginaldata, ZEND_ACC_PUBLIC)
	PHP_ME(Ouchbase_IdentityMap, updateOriginalData, arginfo_ouchbase_identitymap_updateoriginaldata, ZEND_ACC_PUBLIC)
	PHP_ME(Ouchbase_IdentityMap, clear, NULL, ZEND_ACC_PUBLIC)
  PHP_FE_END
};
