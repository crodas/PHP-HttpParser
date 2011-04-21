#ifndef PHP_HTTPPARSER_H
#define PHP_HTTPPARSER_H

#define PHP_HTTPPARSER_EXTNAME  "httpparser"
#define PHP_HTTPPARSER_EXTVER   "0.1"

#include "php.h"

extern zend_module_entry httpparser_module_entry;
extern http_parser_settings httpSettings;

typedef struct {
    zend_object zo;
    http_parser * parser;
} httpParserObj;


#endif /* PHP_httpparser_H */
