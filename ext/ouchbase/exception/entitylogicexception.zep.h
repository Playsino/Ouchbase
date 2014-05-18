
extern zend_class_entry *ouchbase_exception_entitylogicexception_ce;

ZEPHIR_INIT_CLASS(Ouchbase_Exception_EntityLogicException);

PHP_METHOD(Ouchbase_Exception_EntityLogicException, __construct);

ZEND_BEGIN_ARG_INFO_EX(arginfo_ouchbase_exception_entitylogicexception___construct, 0, 0, 1)
	ZEND_ARG_INFO(0, entity)
	ZEND_ARG_INFO(0, message)
	ZEND_ARG_INFO(0, code)
	ZEND_ARG_INFO(0, previous)
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(ouchbase_exception_entitylogicexception_method_entry) {
	PHP_ME(Ouchbase_Exception_EntityLogicException, __construct, arginfo_ouchbase_exception_entitylogicexception___construct, ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)
  PHP_FE_END
};
