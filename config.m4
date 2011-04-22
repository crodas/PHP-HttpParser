dnl $Id$

PHP_ARG_WITH(httpparser, for httpparser support,
    [  --with-httpparser             Include httpparser support])

PHP_ARG_ENABLE(debug, whether to enable debugging support in example,
        [  --enable-example-debug        example: Enable debugging support in example], no, no)

if test "$PHP_httpparser" != "no"; then
  PHP_ADD_INCLUDE(http-parser)
  PHP_NEW_EXTENSION(httpparser, main.c callback.c http-parser/http_parser.c, $ext_shared)
fi
