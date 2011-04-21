/*
  +----------------------------------------------------------------------+
  | Copyright (c) 2011 The PHP Group                                     |
  +----------------------------------------------------------------------+
  | This source file is subject to version 3.0 of the PHP license,       |
  | that is bundled with this package in the file LICENSE, and is        |
  | available through the world-wide-web at the following url:           |
  | http://www.php.net/license/3_0.txt.                                  |
  | If you did not receive a copy of the PHP license and are unable to   |
  | obtain it through the world-wide-web, please send a note to          |
  | license@php.net so we can mail you a copy immediately.               |
  +----------------------------------------------------------------------+
  | Authors: Cesar Rodas <crodas@php.net>                                |
  +----------------------------------------------------------------------+
*/
#include <http_parser.h>
#include <httpparser.h>

/*********************************
    Helper macros
**********************************/
#define CALLBACK_NAME(type) _httpparser_assign ##_## type
#define CALLBACK(type) .on_##type = CALLBACK_NAME(type)
#define FUNCTION(type) \
    int CALLBACK_NAME(type) (http_parser * p, const char * buf, size_t len)  \
    { \
        return httpparser_assign(#type, p, buf, len); \
    } \

#define FUNCTION_EX(type) \
    int CALLBACK_NAME(type) (http_parser * p, const char * buf, size_t len)  \
    { \
        return httpparser_assign_ex(#type, p, buf, len); \
    } \

#define CALL_METHOD(Class, Method, retval, thisptr)  PHP_FN(Class##_##Method)(0, retval, NULL, thisptr, 0 TSRMLS_CC);


int httpparser_assign(char *type, http_parser *p, const char *buf, size_t len)
{
    httpParserObj * Parser;
    Parser = (httpParserObj *)p->data;
    add_assoc_stringl(Parser->variable, type, buf, len, 1);
    return 0;
}

int httpparser_assign_ex(char *type, http_parser *p, const char *buf, size_t len)
{
    zval * dest, **fnd;
    httpParserObj * Parser;
    Parser = (httpParserObj *)p->data;
    if (zend_hash_find(Z_ARRVAL_P(Parser->variable), type, strlen(type)+1, (void**)&fnd) == FAILURE) {
        ALLOC_INIT_ZVAL(dest);
        array_init(dest);
        add_assoc_zval(Parser->variable, type, dest);
    } else {
        dest = *fnd;
    }

    add_next_index_stringl(dest, buf, len, 1);
    return 0;
}

int http_parser_callback(char *type, http_parser *p)
{
    httpParserObj * Parser;
    Parser = (httpParserObj *)p->data;
    zval foo;
    CALL_METHOD(httpparser, parseStr, &foo, Parser->this);

    return 0;
}

FUNCTION(url)
FUNCTION(path)
FUNCTION(body)
FUNCTION(query_string)
FUNCTION(fragment)
FUNCTION_EX(header_field)
FUNCTION_EX(header_value)

http_parser_settings httpSettings = {
    CALLBACK(url),
    CALLBACK(query_string),
    CALLBACK(fragment),
    CALLBACK(path),
    CALLBACK(body),
    CALLBACK(header_field),
    CALLBACK(header_value)
};
