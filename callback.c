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
  | Authors: Cesar Rodas <crodas@php.net                                 |
  +----------------------------------------------------------------------+
*/
#include <http_parser.h>
#include <httpparser.h>

/*********************************
    Helper macros
**********************************/
#define HTTPPARSER_CALLBACK(type) _httpparser_callback ##_## type

#define HTTPPARSER_CREATE_CALLBACK(type) \
    int HTTPPARSER_CALLBACK(type) (http_parser * p, const char * buf, size_t len)  \
    { \
        return httpparser_callback(#type, p, buf, len); \
    } \


int httpparser_callback(char *type, http_parser *p, const char *buf, size_t len)
{
    add_assoc_stringl(p->data, type, buf, len, 1);
    return 0;
}

HTTPPARSER_CREATE_CALLBACK(url)
HTTPPARSER_CREATE_CALLBACK(path)
HTTPPARSER_CREATE_CALLBACK(header_field)
HTTPPARSER_CREATE_CALLBACK(header_value)
HTTPPARSER_CREATE_CALLBACK(body)

http_parser_settings httpSettings = {
    .on_url = HTTPPARSER_CALLBACK(url),
    .on_path = HTTPPARSER_CALLBACK(path),
    .on_body = HTTPPARSER_CALLBACK(body),
    .on_header_field = HTTPPARSER_CALLBACK(header_field),
    .on_header_value = HTTPPARSER_CALLBACK(header_value)
};
