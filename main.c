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

zend_object_handlers httpparser_object_handlers;
zend_class_entry *httpparser_ce;

/*********************************
    Helper macros
**********************************/
#define INIT_OBJECT \
    zval * this = getThis(); \
    httpParserObj * object; \
    http_parser * parser; \
    object = (httpParserObj *) zend_object_store_get_object( this TSRMLS_CC ); \
    if (object == NULL || object->parser == NULL) {    \
        php_error_docref(NULL TSRMLS_CC, E_WARNING, "Constructor was not called");    \
        return; \
    } \
    parser = object->parser;

#define METHOD(type) \
case HTTP_##type: \
    add_assoc_string(return_value, "method", #type, 1); \
    break;
    
    

void httpparser_free_storage(void *pointer TSRMLS_DC)
{

    httpParserObj * object = pointer;
    efree(object->parser);
    efree(object);
}


PHP_METHOD(httpparser, __construct)
{
    INIT_OBJECT
}


PHP_METHOD(httpparser, parse)
{
    INIT_OBJECT
    char * buf;
    int len;
    size_t size;
    zend_bool is_request = 1;


    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s|b", &buf, &len, &is_request) == FAILURE) {
        return;
    }
    
    http_parser_init(parser, is_request ? HTTP_REQUEST : HTTP_RESPONSE);

    /* initialize the http_parser */
    array_init(return_value);
    parser->data = return_value;
    
    size = http_parser_execute(parser, &httpSettings, buf, (size_t) len);

    if ((size_t)size != (size_t)len) {
        printf("[%d] [%d] (%d)\n", size, len, is_request);fflush(stdout);
        RETURN_FALSE;
    }

    if (is_request) {
        switch (parser->method) {
            METHOD(DELETE)
            METHOD(GET)
            METHOD(HEAD)
            METHOD(POST)
            METHOD(PUT)
            /* pathological */
            METHOD(CONNECT)
            METHOD(OPTIONS)
            METHOD(TRACE)
            /* webdav */
            METHOD(COPY)
            METHOD(LOCK)
            METHOD(MKCOL)
            METHOD(MOVE)
            METHOD(PROPFIND)
            METHOD(PROPPATCH)
            METHOD(UNLOCK)
            /* subversion */
            METHOD(REPORT)
            METHOD(MKACTIVITY)
            METHOD(CHECKOUT)
            METHOD(MERGE)
            /* upnp */
            METHOD(MSEARCH)
            METHOD(NOTIFY)
            METHOD(SUBSCRIBE)
            METHOD(UNSUBSCRIBE)
        }
    } else {
        add_assoc_long(return_value, "status_code", (long)parser->status_code);
    }

    add_assoc_long(return_value, "version_minor", (long)parser->http_minor);
    add_assoc_long(return_value, "version_major", (long)parser->http_major);

}


zend_object_value httpparser_create_handler(zend_class_entry *type TSRMLS_DC)
{
    zval *tmp;
    zend_object_value retval;
    httpParserObj * obj;
    
    /* malloc for object and the http_parser struct */
    obj = emalloc(sizeof(httpParserObj));
    obj->parser = emalloc(sizeof(http_parser));


    /* initialize the object */
    zend_object_std_init(&obj->zo, type TSRMLS_CC);
    
    retval.handle   = zend_objects_store_put(obj, NULL, httpparser_free_storage, NULL TSRMLS_CC);
    retval.handlers = &httpparser_object_handlers;
    
    return retval;
}

function_entry httpparser_methods[] = {
    PHP_ME(httpparser, __construct,    NULL,                        ZEND_ACC_PUBLIC | ZEND_ACC_CTOR)
    PHP_ME(httpparser, parse,     NULL,                             ZEND_ACC_PUBLIC)
    /*PHP_ME(httpparser, __destruct,     NULL,                       ZEND_ACC_PUBLIC | ZEND_ACC_DTOR)
    PHP_ME(httpparser, execute,        arginfo_httpparser_execute, ZEND_ACC_PUBLIC)
    PHP_ME(httpparser, hasError,       NULL,                       ZEND_ACC_PUBLIC)
    PHP_ME(httpparser, isFinished,     NULL,                       ZEND_ACC_PUBLIC)
    PHP_ME(httpparser, getEnvironment, NULL,                       ZEND_ACC_PUBLIC) */

    {NULL, NULL, NULL}
};

PHP_MINIT_FUNCTION(httpparser)
{
    zend_class_entry ce;
    INIT_CLASS_ENTRY(ce, "httpparser", httpparser_methods);
    httpparser_ce = zend_register_internal_class(&ce TSRMLS_CC);
    httpparser_ce->create_object = httpparser_create_handler;

    memcpy(&httpparser_object_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));
    httpparser_object_handlers.clone_obj = NULL;

    return SUCCESS;
}

zend_module_entry httpparser_module_entry = {
#if ZEND_MODULE_API_NO >= 20010901
    STANDARD_MODULE_HEADER,
#endif
    PHP_HTTPPARSER_EXTNAME,
    NULL,        /* Functions */
    PHP_MINIT(httpparser),        /* MINIT */
    NULL,        /* MSHUTDOWN */
    NULL,        /* RINIT */
    NULL,        /* RSHUTDOWN */
    NULL,        /* MINFO */
#if ZEND_MODULE_API_NO >= 20010901
    PHP_HTTPPARSER_EXTVER,
#endif
    STANDARD_MODULE_PROPERTIES
};


ZEND_GET_MODULE(httpparser)
