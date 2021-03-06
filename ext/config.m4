PHP_ARG_ENABLE(ouchbase, whether to enable ouchbase, [ --enable-ouchbase   Enable Ouchbase])

if test "$PHP_OUCHBASE" = "yes"; then
	AC_DEFINE(HAVE_OUCHBASE, 1, [Whether you have Ouchbase])
	ouchbase_sources="ouchbase.c kernel/main.c kernel/memory.c kernel/exception.c kernel/hash.c kernel/debug.c kernel/backtrace.c kernel/object.c kernel/array.c kernel/extended/array.c kernel/string.c kernel/fcall.c kernel/require.c kernel/file.c kernel/operators.c kernel/concat.c kernel/variables.c kernel/filter.c kernel/iterator.c kernel/exit.c ouchbase/entity.zep.c
	ouchbase/entitymanager.zep.c
	ouchbase/entityproxy.zep.c
	ouchbase/exception/couchbaseexception.zep.c
	ouchbase/exception/entitylogicexception.zep.c
	ouchbase/exception/entitymanagerexception.zep.c
	ouchbase/exception/entitymodifiedexception.zep.c
	ouchbase/exception/entityupdatefailedexception.zep.c
	ouchbase/identitymap.zep.c
	ouchbase/repository.zep.c
	ouchbase/unitofwork.zep.c
	ouchbase/_etc.zep.c "
	PHP_NEW_EXTENSION(ouchbase, $ouchbase_sources, $ext_shared)

	old_CPPFLAGS=$CPPFLAGS
	CPPFLAGS="$CPPFLAGS $INCLUDES"

	AC_CHECK_DECL(
		[HAVE_BUNDLED_PCRE],
		[
			AC_CHECK_HEADERS(
				[ext/pcre/php_pcre.h],
				[
					PHP_ADD_EXTENSION_DEP([ouchbase], [pcre])
					AC_DEFINE([ZEPHIR_USE_PHP_PCRE], [1], [Whether PHP pcre extension is present at compile time])
				],
				,
				[[#include "main/php.h"]]
			)
		],
		,
		[[#include "php_config.h"]]
	)

	AC_CHECK_DECL(
		[HAVE_JSON],
		[
			AC_CHECK_HEADERS(
				[ext/json/php_json.h],
				[
					PHP_ADD_EXTENSION_DEP([ouchbase], [json])
					AC_DEFINE([ZEPHIR_USE_PHP_JSON], [1], [Whether PHP json extension is present at compile time])
				],
				,
				[[#include "main/php.h"]]
			)
		],
		,
		[[#include "php_config.h"]]
	)

	CPPFLAGS=$old_CPPFLAGS
fi
