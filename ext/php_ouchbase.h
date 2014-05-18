
/* This file was generated automatically by Zephir do not modify it! */

#ifndef PHP_OUCHBASE_H
#define PHP_OUCHBASE_H 1

#define ZEPHIR_RELEASE 1

#include "kernel/globals.h"

#define PHP_OUCHBASE_NAME        "Ouchbase"
#define PHP_OUCHBASE_VERSION     "0.0.1"
#define PHP_OUCHBASE_EXTNAME     "ouchbase"
#define PHP_OUCHBASE_AUTHOR      "Ihor Burlachenko"
#define PHP_OUCHBASE_ZEPVERSION  "0.4.2a"
#define PHP_OUCHBASE_DESCRIPTION "Object key/value mapper (OKVM) for Couchbase."



ZEND_BEGIN_MODULE_GLOBALS(ouchbase)

	/* Memory */
	zephir_memory_entry *start_memory; /**< The first preallocated frame */
	zephir_memory_entry *end_memory; /**< The last preallocate frame */
	zephir_memory_entry *active_memory; /**< The current memory frame */

	/* Virtual Symbol Tables */
	zephir_symbol_table *active_symbol_table;

	/** Function cache */
	HashTable *fcache;

	/* Max recursion control */
	unsigned int recursive_lock;

	/* Global constants */
	zval *global_true;
	zval *global_false;
	zval *global_null;
	
ZEND_END_MODULE_GLOBALS(ouchbase)

#ifdef ZTS
#include "TSRM.h"
#endif

ZEND_EXTERN_MODULE_GLOBALS(ouchbase)

#ifdef ZTS
	#define ZEPHIR_GLOBAL(v) TSRMG(ouchbase_globals_id, zend_ouchbase_globals *, v)
#else
	#define ZEPHIR_GLOBAL(v) (ouchbase_globals.v)
#endif

#ifdef ZTS
	#define ZEPHIR_VGLOBAL ((zend_ouchbase_globals *) (*((void ***) tsrm_ls))[TSRM_UNSHUFFLE_RSRC_ID(ouchbase_globals_id)])
#else
	#define ZEPHIR_VGLOBAL &(ouchbase_globals)
#endif

#define zephir_globals_def ouchbase_globals
#define zend_zephir_globals_def zend_ouchbase_globals

extern zend_module_entry ouchbase_module_entry;
#define phpext_ouchbase_ptr &ouchbase_module_entry

#endif
