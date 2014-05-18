
extern zend_class_entry *ouchbase_repository_ce;

ZEPHIR_INIT_CLASS(Ouchbase_Repository);

PHP_METHOD(Ouchbase_Repository, __construct);
PHP_METHOD(Ouchbase_Repository, find);
PHP_METHOD(Ouchbase_Repository, refresh);
PHP_METHOD(Ouchbase_Repository, findAll);
PHP_METHOD(Ouchbase_Repository, insert);
PHP_METHOD(Ouchbase_Repository, update);
PHP_METHOD(Ouchbase_Repository, delete);
PHP_METHOD(Ouchbase_Repository, executeWithoutTimeouts);
PHP_METHOD(Ouchbase_Repository, getKey);
PHP_METHOD(Ouchbase_Repository, getClassReflection);
PHP_METHOD(Ouchbase_Repository, getPropertyReflection);
PHP_METHOD(Ouchbase_Repository, __getWithCas);
PHP_METHOD(Ouchbase_Repository, __getMultiWithCas);
PHP_METHOD(Ouchbase_Repository, toArray);
PHP_METHOD(Ouchbase_Repository, toObject);

ZEND_BEGIN_ARG_INFO_EX(arginfo_ouchbase_repository___construct, 0, 0, 3)
	ZEND_ARG_INFO(0, unitOfWork)
	ZEND_ARG_INFO(0, identityMap)
	ZEND_ARG_INFO(0, couchbase)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_ouchbase_repository_find, 0, 0, 1)
	ZEND_ARG_INFO(0, id)
	ZEND_ARG_INFO(0, concurrent)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_ouchbase_repository_refresh, 0, 0, 1)
	ZEND_ARG_INFO(0, entity)
	ZEND_ARG_INFO(0, concurrent)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_ouchbase_repository_findall, 0, 0, 1)
	ZEND_ARG_INFO(0, ids)
	ZEND_ARG_INFO(0, concurrent)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_ouchbase_repository_insert, 0, 0, 1)
	ZEND_ARG_INFO(0, entity)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_ouchbase_repository_update, 0, 0, 1)
	ZEND_ARG_INFO(0, entity)
	ZEND_ARG_INFO(0, cas)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_ouchbase_repository_delete, 0, 0, 1)
	ZEND_ARG_INFO(0, entity)
	ZEND_ARG_INFO(0, cas)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_ouchbase_repository_executewithouttimeouts, 0, 0, 1)
	ZEND_ARG_INFO(0, method)
	ZEND_ARG_INFO(0, args)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_ouchbase_repository_getkey, 0, 0, 1)
	ZEND_ARG_INFO(0, id)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_ouchbase_repository_getpropertyreflection, 0, 0, 1)
	ZEND_ARG_INFO(0, property)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_ouchbase_repository___getwithcas, 0, 0, 1)
	ZEND_ARG_INFO(0, id)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_ouchbase_repository___getmultiwithcas, 0, 0, 1)
	ZEND_ARG_INFO(0, ids)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_ouchbase_repository_toarray, 0, 0, 1)
	ZEND_ARG_INFO(0, entity)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_ouchbase_repository_toobject, 0, 0, 1)
	ZEND_ARG_INFO(0, data)
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(ouchbase_repository_method_entry) {
	PHP_ME(Ouchbase_Repository, __construct, arginfo_ouchbase_repository___construct, ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)
	PHP_ME(Ouchbase_Repository, find, arginfo_ouchbase_repository_find, ZEND_ACC_PUBLIC)
	PHP_ME(Ouchbase_Repository, refresh, arginfo_ouchbase_repository_refresh, ZEND_ACC_PUBLIC)
	PHP_ME(Ouchbase_Repository, findAll, arginfo_ouchbase_repository_findall, ZEND_ACC_PUBLIC)
	PHP_ME(Ouchbase_Repository, insert, arginfo_ouchbase_repository_insert, ZEND_ACC_PUBLIC)
	PHP_ME(Ouchbase_Repository, update, arginfo_ouchbase_repository_update, ZEND_ACC_PUBLIC)
	PHP_ME(Ouchbase_Repository, delete, arginfo_ouchbase_repository_delete, ZEND_ACC_PUBLIC)
	PHP_ME(Ouchbase_Repository, executeWithoutTimeouts, arginfo_ouchbase_repository_executewithouttimeouts, ZEND_ACC_PROTECTED)
	PHP_ME(Ouchbase_Repository, getKey, arginfo_ouchbase_repository_getkey, ZEND_ACC_PUBLIC)
	PHP_ME(Ouchbase_Repository, getClassReflection, NULL, ZEND_ACC_PROTECTED)
	PHP_ME(Ouchbase_Repository, getPropertyReflection, arginfo_ouchbase_repository_getpropertyreflection, ZEND_ACC_PROTECTED)
	PHP_ME(Ouchbase_Repository, __getWithCas, arginfo_ouchbase_repository___getwithcas, ZEND_ACC_PUBLIC)
	PHP_ME(Ouchbase_Repository, __getMultiWithCas, arginfo_ouchbase_repository___getmultiwithcas, ZEND_ACC_PUBLIC)
	PHP_ME(Ouchbase_Repository, toArray, arginfo_ouchbase_repository_toarray, ZEND_ACC_ABSTRACT|ZEND_ACC_PUBLIC)
	PHP_ME(Ouchbase_Repository, toObject, arginfo_ouchbase_repository_toobject, ZEND_ACC_ABSTRACT|ZEND_ACC_PUBLIC)
  PHP_FE_END
};
