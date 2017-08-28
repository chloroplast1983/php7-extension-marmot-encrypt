/*
  +----------------------------------------------------------------------+
  | PHP Version 7                                                        |
  +----------------------------------------------------------------------+
  | Copyright (c) 1997-2016 The PHP Group                                |
  +----------------------------------------------------------------------+
  | This source file is subject to version 3.01 of the PHP license,      |
  | that is bundled with this package in the file LICENSE, and is        |
  | available through the world-wide-web at the following url:           |
  | http://www.php.net/license/3_01.txt                                  |
  | If you did not receive a copy of the PHP license and are unable to   |
  | obtain it through the world-wide-web, please send a note to          |
  | license@php.net so we can mail you a copy immediately.               |
  +----------------------------------------------------------------------+
  | Author:                                                              |
  +----------------------------------------------------------------------+
*/

/* $Id$ */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <string.h>

#include "php.h"
#include "php_ini.h"
#include "ext/standard/info.h"
#include "php_marmot.h"

#include "ext/standard/info.h"
#include "ext/standard/base64.h"
#include "ext/standard/php_string.h"

/* If you declare any globals in php_marmot.h uncomment this:
ZEND_DECLARE_MODULE_GLOBALS(marmot)
*/

/* True global resources - no need for thread safety here */
static int le_marmot;

/* {{{ PHP_INI
 */
/* Remove comments and fill if you need to have entries in php.ini
PHP_INI_BEGIN()
    STD_PHP_INI_ENTRY("marmot.global_value",      "42", PHP_INI_ALL, OnUpdateLong, global_value, zend_marmot_globals, marmot_globals)
    STD_PHP_INI_ENTRY("marmot.global_string", "foobar", PHP_INI_ALL, OnUpdateString, global_string, zend_marmot_globals, marmot_globals)
PHP_INI_END()
*/
/* }}} */

/* Remove the following function when you have successfully modified config.m4
   so that your module can be compiled into PHP, it exists only for testing
   purposes. */

/* Every user-visible function in PHP should document itself in the source */
/* {{{ proto string confirm_marmot_compiled(string arg)
   Return a string to confirm that the module is compiled in */
PHP_FUNCTION(confirm_marmot_compiled)
{
	char *arg = NULL;
	size_t arg_len, len;
	zend_string *strg;

	if (zend_parse_parameters(ZEND_NUM_ARGS(), "s", &arg, &arg_len) == FAILURE) {
		return;
	}

	strg = strpprintf(0, "Congratulations! You have successfully modified ext/%.78s/config.m4. Module %.78s is now compiled into PHP.", "marmot", arg);

	RETURN_STR(strg);
}

PHP_FUNCTION(marmot_encode) {

	char *input, *result, *convert_str;
	size_t input_len;
	int i,ord_long;
	zend_string *ret;

	if (zend_parse_parameters(ZEND_NUM_ARGS(), "s", &input, &input_len) == FAILURE) {
			return;
	}
	convert_str = (char *)emalloc(input_len+1);

  for(i=0; i<input_len; i++)
  {
      ord_long = (int)((unsigned char)input[i]);
      switch(i%6)
      {
          case 0:
              convert_str[i] = (char)(ord_long-1);
              break;
          case 1:
              convert_str[i] = (char)(ord_long-5);
              break;
          case 2:
              convert_str[i] = (char)(ord_long-7);
              break;
          case 3:
              convert_str[i] = (char)(ord_long-2);
              break;
          case 4:
              convert_str[i] = (char)(ord_long-4);
              break;
          case 5:
              convert_str[i] = (char)(ord_long-9);
              break;
          default:;
      }
  }
  convert_str[input_len] = '\0';

	// zend_string *php_base64_encode(const unsigned char *, size_t);
	ret = php_base64_encode((unsigned char*)convert_str, input_len);
  if(ret == NULL)
  {
      RETURN_FALSE;
  }

  //mode 1 : trim left
  //mode 2 : trim right
  //mode 3 : trim left and right
  //zend_string *php_trim(zend_string *str, char *what, size_t what_len, int mode)
  ret = php_trim(ret, "=", 1,3);
  result = php_strtr(ZSTR_VAL(ret),ZSTR_LEN(ret), "+/", "-_", 2);

  RETURN_STRING(result);
}

PHP_FUNCTION(marmot_decode) {

        char *input, *result, *convert_str, *out_put;
        size_t input_len, result_len;
        int i, ord_long;
        zend_string *ret, *zend_input_string;
        // zend_string &

        if (zend_parse_parameters(ZEND_NUM_ARGS(), "s", &input, &input_len) == FAILURE) {
                return;
        }

        zend_input_string = zend_string_init(input, input_len, 0);
        convert_str = php_strtr(ZSTR_VAL(zend_input_string),ZSTR_LEN(zend_input_string), "-_", "+/", 2);

        ret = php_base64_decode_ex((unsigned char*)convert_str, input_len, 1);
        if (ret == NULL) {
                RETURN_FALSE;
        }

        out_put = ZSTR_VAL(ret);
        result_len = ZSTR_LEN(ret);

        result = (char *)emalloc(result_len+1);
        for(i=0; i<result_len; i++)
        {
                ord_long = (int)((unsigned char)out_put[i]);
                switch(i%6)
                {
                        case 0:
                                result[i] = (char)(ord_long+1);
                                break;
                        case 1:
                                result[i] = (char)(ord_long+5);
                                break;
                        case 2:
                                result[i] = (char)(ord_long+7);
                                break;
                        case 3:
                                result[i] = (char)(ord_long+2);
                                break;
                        case 4:
                                result[i] = (char)(ord_long+4);
                                break;
                        case 5:
              result[i] = (char)(ord_long+9);
              break;
          default:;
      }
  }
  result[result_len] = '\0';

  RETURN_STRING(result);
}
/* }}} */
/* The previous line is meant for vim and emacs, so it can correctly fold and
   unfold functions in source code. See the corresponding marks just before
   function definition, where the functions purpose is also documented. Please
   follow this convention for the convenience of others editing your code.
*/


/* {{{ php_marmot_init_globals
 */
/* Uncomment this function if you have INI entries
static void php_marmot_init_globals(zend_marmot_globals *marmot_globals)
{
	marmot_globals->global_value = 0;
	marmot_globals->global_string = NULL;
}
*/
/* }}} */

/* {{{ PHP_MINIT_FUNCTION
 */
PHP_MINIT_FUNCTION(marmot)
{
	/* If you have INI entries, uncomment these lines
	REGISTER_INI_ENTRIES();
	*/
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MSHUTDOWN_FUNCTION
 */
PHP_MSHUTDOWN_FUNCTION(marmot)
{
	/* uncomment this line if you have INI entries
	UNREGISTER_INI_ENTRIES();
	*/
	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request start */
/* {{{ PHP_RINIT_FUNCTION
 */
PHP_RINIT_FUNCTION(marmot)
{
#if defined(COMPILE_DL_MARMOT) && defined(ZTS)
	ZEND_TSRMLS_CACHE_UPDATE();
#endif
	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request end */
/* {{{ PHP_RSHUTDOWN_FUNCTION
 */
PHP_RSHUTDOWN_FUNCTION(marmot)
{
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MINFO_FUNCTION
 */
PHP_MINFO_FUNCTION(marmot)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "marmot support", "enabled");
	php_info_print_table_end();

	/* Remove comments if you have entries in php.ini
	DISPLAY_INI_ENTRIES();
	*/
}
/* }}} */

/* {{{ marmot_functions[]
 *
 * Every user visible function must have an entry in marmot_functions[].
 */
const zend_function_entry marmot_functions[] = {
	PHP_FE(confirm_marmot_compiled,	NULL)		/* For testing, remove later. */
	PHP_FE(marmot_encode,  NULL)
	PHP_FE(marmot_decode,  NULL)
	PHP_FE_END	/* Must be the last line in marmot_functions[] */
};
/* }}} */

/* {{{ marmot_module_entry
 */
zend_module_entry marmot_module_entry = {
	STANDARD_MODULE_HEADER,
	"marmot",
	marmot_functions,
	PHP_MINIT(marmot),
	PHP_MSHUTDOWN(marmot),
	PHP_RINIT(marmot),		/* Replace with NULL if there's nothing to do at request start */
	PHP_RSHUTDOWN(marmot),	/* Replace with NULL if there's nothing to do at request end */
	PHP_MINFO(marmot),
	PHP_MARMOT_VERSION,
	STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_MARMOT
#ifdef ZTS
ZEND_TSRMLS_CACHE_DEFINE();
#endif
ZEND_GET_MODULE(marmot)
#endif

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
