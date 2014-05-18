
extern zend_class_entry *ouchbase_entityproxy_ce;

ZEPHIR_INIT_CLASS(Ouchbase_EntityProxy);

PHP_METHOD(Ouchbase_EntityProxy, __construct);
PHP_METHOD(Ouchbase_EntityProxy, getId);
PHP_METHOD(Ouchbase_EntityProxy, getEntity);
PHP_METHOD(Ouchbase_EntityProxy, isProxied);
PHP_METHOD(Ouchbase_EntityProxy, __get);
PHP_METHOD(Ouchbase_EntityProxy, __set);
PHP_METHOD(Ouchbase_EntityProxy, __call);
PHP_METHOD(Ouchbase_EntityProxy, __invoke);

ZEND_BEGIN_ARG_INFO_EX(arginfo_ouchbase_entityproxy___construct, 0, 0, 1)
	ZEND_ARG_INFO(0, creator)
	ZEND_ARG_INFO(0, id)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_ouchbase_entityproxy___get, 0, 0, 1)
	ZEND_ARG_INFO(0, property)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_ouchbase_entityproxy___set, 0, 0, 2)
	ZEND_ARG_INFO(0, property)
	ZEND_ARG_INFO(0, value)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_ouchbase_entityproxy___call, 0, 0, 2)
	ZEND_ARG_INFO(0, method)
	ZEND_ARG_INFO(0, args)
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(ouchbase_entityproxy_method_entry) {
	PHP_ME(Ouchbase_EntityProxy, __construct, arginfo_ouchbase_entityproxy___construct, ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)
	PHP_ME(Ouchbase_EntityProxy, getId, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Ouchbase_EntityProxy, getEntity, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Ouchbase_EntityProxy, isProxied, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Ouchbase_EntityProxy, __get, arginfo_ouchbase_entityproxy___get, ZEND_ACC_PUBLIC)
	PHP_ME(Ouchbase_EntityProxy, __set, arginfo_ouchbase_entityproxy___set, ZEND_ACC_PUBLIC)
	PHP_ME(Ouchbase_EntityProxy, __call, arginfo_ouchbase_entityproxy___call, ZEND_ACC_PUBLIC)
	PHP_ME(Ouchbase_EntityProxy, __invoke, NULL, ZEND_ACC_PUBLIC)
  PHP_FE_END
};
