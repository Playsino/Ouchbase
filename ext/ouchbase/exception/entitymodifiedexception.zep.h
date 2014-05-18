
extern zend_class_entry *ouchbase_exception_entitymodifiedexception_ce;

ZEPHIR_INIT_CLASS(Ouchbase_Exception_EntityModifiedException);

PHP_METHOD(Ouchbase_Exception_EntityModifiedException, __construct);
PHP_METHOD(Ouchbase_Exception_EntityModifiedException, getAction);
PHP_METHOD(Ouchbase_Exception_EntityModifiedException, setAction);
PHP_METHOD(Ouchbase_Exception_EntityModifiedException, getEntity);

ZEND_BEGIN_ARG_INFO_EX(arginfo_ouchbase_exception_entitymodifiedexception___construct, 0, 0, 1)
	ZEND_ARG_INFO(0, entity)
	ZEND_ARG_INFO(0, message)
	ZEND_ARG_INFO(0, code)
	ZEND_ARG_INFO(0, previous)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_ouchbase_exception_entitymodifiedexception_setaction, 0, 0, 1)
	ZEND_ARG_INFO(0, action)
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(ouchbase_exception_entitymodifiedexception_method_entry) {
	PHP_ME(Ouchbase_Exception_EntityModifiedException, __construct, arginfo_ouchbase_exception_entitymodifiedexception___construct, ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)
	PHP_ME(Ouchbase_Exception_EntityModifiedException, getAction, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Ouchbase_Exception_EntityModifiedException, setAction, arginfo_ouchbase_exception_entitymodifiedexception_setaction, ZEND_ACC_PUBLIC)
	PHP_ME(Ouchbase_Exception_EntityModifiedException, getEntity, NULL, ZEND_ACC_PUBLIC)
  PHP_FE_END
};
