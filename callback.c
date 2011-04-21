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
#define CALLBACK_NAME(type) _httpparser_callback ##_## type
#define CALLBACK(type) .on_##type = CALLBACK_NAME(type)
#define CREATE_CALLBACK(type) \
    int CALLBACK_NAME(type) (http_parser * p, const char * buf, size_t len)  \
    { \
        return httpparser_callback(#type, p, buf, len); \
    } \

#define CREATE_CALLBACK_EX(type) \
    int CALLBACK_NAME(type) (http_parser * p, const char * buf, size_t len)  \
    { \
        return httpparser_callback_ex(#type, p, buf, len); \
    } \


int httpparser_callback(char *type, http_parser *p, const char *buf, size_t len)
{
    add_assoc_stringl(p->data, type, buf, len, 1);
    return 0;
}

int httpparser_callback_ex(char *type, http_parser *p, const char *buf, size_t len)
{
    zval * dest, **fnd, *tmp;
    tmp = (zval *)p->data;
    if (zend_hash_find(Z_ARRVAL_P(tmp), type, strlen(type)+1, (void**)&fnd) == FAILURE) {
        ALLOC_INIT_ZVAL(dest);
        array_init(dest);
        add_assoc_zval(p->data, type, dest);
    } else {
        dest = *fnd;
    }

    add_next_index_stringl(dest, buf, len, 1);
    return 0;
}

CREATE_CALLBACK(url)
CREATE_CALLBACK(path)
CREATE_CALLBACK_EX(header_field)
CREATE_CALLBACK_EX(header_value)
CREATE_CALLBACK(body)
CREATE_CALLBACK(query_string)
CREATE_CALLBACK(fragment)

http_parser_settings httpSettings = {
    CALLBACK(url),
    CALLBACK(query_string),
    CALLBACK(fragment),
    CALLBACK(path),
    CALLBACK(body),
    CALLBACK(header_field),
    CALLBACK(header_value)
};
