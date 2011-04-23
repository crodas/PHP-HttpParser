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
#ifndef PHP_HTTPPARSER_H
#define PHP_HTTPPARSER_H

#define PHP_HTTPPARSER_EXTNAME  "httpparser"
#define PHP_HTTPPARSER_EXTVER   "0.1"

#include "php.h"

extern zend_module_entry httpparser_module_entry;

extern http_parser_settings httpSettings;

typedef struct {
    /* zend object */
    zend_object this;
    zval * pThis;

    /* http_parser struct */
    http_parser * parser;

    /* variable where to store the parsed HTTP */
    zval * variable;
    enum http_parser_type status;
    short type;

    /* should we free the zval * variable? */
    short free_variable;
    
} httpParserObj;

#endif /* PHP_httpparser_H */
