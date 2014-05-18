
extern zend_class_entry *ouchbase__etc_ce;

ZEPHIR_INIT_CLASS(Ouchbase__etc);

PHP_METHOD(Ouchbase__etc, getEntityClass);
PHP_METHOD(Ouchbase__etc, getEntityHash);

ZEND_BEGIN_ARG_INFO_EX(arginfo_ouchbase__etc_getentityclass, 0, 0, 1)
	ZEND_ARG_INFO(0, entity)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_ouchbase__etc_getentityhash, 0, 0, 1)
	ZEND_ARG_INFO(0, className)
	ZEND_ARG_INFO(0, id)
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(ouchbase__etc_method_entry) {
	PHP_ME(Ouchbase__etc, getEntityClass, arginfo_ouchbase__etc_getentityclass, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Ouchbase__etc, getEntityHash, arginfo_ouchbase__etc_getentityhash, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
  PHP_FE_END
};
