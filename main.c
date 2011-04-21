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
zend_class_entry *httpparser_ce, *httpparser_exception_ce;

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

#define CHECK_HTTP_METHOD(type) \
case HTTP_##type: \
    return #type; \
    

// char * _httpparser_get_method(http_parsre * parser) {{{
/**
 *  Return the string value of the request method
 *
 */
static char * _httpparser_get_method(http_parser * parser)
{
    switch (parser->method) {
        CHECK_HTTP_METHOD(DELETE)
        CHECK_HTTP_METHOD(GET)
        CHECK_HTTP_METHOD(HEAD)
        CHECK_HTTP_METHOD(POST)
        CHECK_HTTP_METHOD(PUT)
        /* pathological */
        CHECK_HTTP_METHOD(CONNECT)
        CHECK_HTTP_METHOD(OPTIONS)
        CHECK_HTTP_METHOD(TRACE)
        /* webdav */
        CHECK_HTTP_METHOD(COPY)
        CHECK_HTTP_METHOD(LOCK)
        CHECK_HTTP_METHOD(MKCOL)
        CHECK_HTTP_METHOD(MOVE)
        CHECK_HTTP_METHOD(PROPFIND)
        CHECK_HTTP_METHOD(PROPPATCH)
        CHECK_HTTP_METHOD(UNLOCK)
        /* subversion */
        CHECK_HTTP_METHOD(REPORT)
        CHECK_HTTP_METHOD(MKACTIVITY)
        CHECK_HTTP_METHOD(CHECKOUT)
        CHECK_HTTP_METHOD(MERGE)
        /* upnp */
        CHECK_HTTP_METHOD(MSEARCH)
        CHECK_HTTP_METHOD(NOTIFY)
        CHECK_HTTP_METHOD(SUBSCRIBE)
        CHECK_HTTP_METHOD(UNSUBSCRIBE)
    }
}
// }}}

static httpParserObj * _httpparser_new()
{
    httpParserObj * object;

    object = emalloc(sizeof(httpParserObj));
    memset(object, 0,  sizeof(httpParserObj));
    object->parser = emalloc(sizeof(http_parser));

    return object;
}

static void _httpparser_free_storage(void *pointer TSRMLS_DC)
{

    httpParserObj * object = pointer;
    efree(object->parser);
    efree(object);
}

static void _httpparser_throw_exception(char * message, int offset TSRMLS_DC)
{
    zval * object;
    char exception[220];
    MAKE_STD_ZVAL(object);
    
    sprintf(exception, "%s at char %d", message, offset);

    object_init_ex(object, httpparser_exception_ce);
    zend_update_property_string(httpparser_exception_ce, object, "message", sizeof("message") - 1,
        exception TSRMLS_CC);
    zend_update_property_long(httpparser_exception_ce, object, "offset", sizeof("offset") - 1,
        (long)offset TSRMLS_CC);
    zend_throw_exception_object(object TSRMLS_CC);
}

PHP_METHOD(httpparser, parse)
{
    INIT_OBJECT
    char * buf;
    int len;
    size_t offset;
    zend_bool is_request = 1;


    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s|b", &buf, &len, &is_request) == FAILURE) {
        return;
    }
}

PHP_METHOD(httpparser, parseStr)
{
    char * buf;
    int len;
    size_t offset;
    zend_bool is_request = 1;
    httpParserObj * object;

    object = _httpparser_new();

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s|b", &buf, &len, &is_request) == FAILURE) {
        return;
    }
    
    http_parser_init(object->parser, is_request ? HTTP_REQUEST : HTTP_RESPONSE);

    /* initialize the http_parser */
    array_init(return_value);
    object->variable = return_value;
    object->parser->data = object;
    
    offset = http_parser_execute(object->parser, &httpSettings, buf, (size_t) len);

    if ((size_t)offset != (size_t)len) {
        _httpparser_throw_exception("Error while parsing HTTP", offset TSRMLS_CC);
        return;
    }

    if (is_request) {
        add_assoc_string(return_value, "method", _httpparser_get_method(object->parser), 1);
    } else {
        add_assoc_long(return_value, "status_code", (long)object->parser->status_code);
    }

    add_assoc_long(return_value, "version_minor", (long)object->parser->http_minor);
    add_assoc_long(return_value, "version_major", (long)object->parser->http_major);

    _httpparser_free_storage(object);
}

zend_object_value httpparser_create_handler(zend_class_entry *type TSRMLS_DC)
{
    zval *tmp;
    zend_object_value retval;
    httpParserObj * obj;
    
    /* malloc for object and the http_parser struct */
    obj = _httpparser_new(); 

    /* initialize the object */
    zend_object_std_init(&obj->this, type TSRMLS_CC);
    
    retval.handle   = zend_objects_store_put(obj, NULL, _httpparser_free_storage, NULL TSRMLS_CC);
    retval.handlers = &httpparser_object_handlers;
    
    return retval;
}

function_entry httpparser_methods[] = {
    PHP_ME(httpparser, parse,     NULL,      ZEND_ACC_PUBLIC | ZEND_ACC_FINAL)
    PHP_ME(httpparser, parseStr,     NULL,   ZEND_ACC_PUBLIC | ZEND_ACC_STATIC | ZEND_ACC_FINAL)

    // events
    ZEND_FENTRY(onMessageBegin,     NULL, NULL,  ZEND_ACC_PUBLIC | ZEND_ACC_ABSTRACT)
    ZEND_FENTRY(onHeadersComplete,  NULL, NULL,  ZEND_ACC_PUBLIC | ZEND_ACC_ABSTRACT)
    ZEND_FENTRY(onMessageComplete,  NULL, NULL,  ZEND_ACC_PUBLIC | ZEND_ACC_ABSTRACT)
    {NULL, NULL, NULL}
};

PHP_MINIT_FUNCTION(httpparser)
{
    zend_class_entry ce, exception_ce;
    INIT_CLASS_ENTRY(ce, "httpparser", httpparser_methods);
    httpparser_ce = zend_register_internal_class(&ce TSRMLS_CC);
    httpparser_ce->create_object = httpparser_create_handler;

    INIT_CLASS_ENTRY(exception_ce, "httpparser_exception", NULL);

    httpparser_exception_ce = zend_register_internal_class_ex(&exception_ce,  zend_exception_get_default(TSRMLS_C), NULL TSRMLS_CC);


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
