
#ifdef HAVE_CONFIG_H
#include "../../ext_config.h"
#endif

#include <php.h>
#include "../../php_ext.h"
#include "../../ext.h"

#include <Zend/zend_operators.h>
#include <Zend/zend_exceptions.h>
#include <Zend/zend_interfaces.h>

#include "kernel/main.h"


ZEPHIR_INIT_CLASS(Ouchbase_Exception_EntityUpdateFailedException) {

	ZEPHIR_REGISTER_CLASS_EX(Ouchbase\\Exception, EntityUpdateFailedException, ouchbase, exception_entityupdatefailedexception, spl_ce_RuntimeException, NULL, 0);

	return SUCCESS;

}

