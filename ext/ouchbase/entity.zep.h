
extern zend_class_entry *ouchbase_entity_ce;

ZEPHIR_INIT_CLASS(Ouchbase_Entity);

ZEPHIR_INIT_FUNCS(ouchbase_entity_method_entry) {
	PHP_ABSTRACT_ME(Ouchbase_Entity, getId, NULL)
  PHP_FE_END
};
