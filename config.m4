dnl $Id$

PHP_ARG_WITH(httpparser, for httpparser support,
    [  --with-httpparser             Include httpparser support])

PHP_ARG_ENABLE(debug, whether to enable debugging support in example,
        [  --enable-example-debug        example: Enable debugging support in example], no, no)

if test "$PHP_httpparser" != "no"; then
  dnl Write more examples of tests here...

  dnl # --with-httpparser -> check with-path
  dnl SEARCH_PATH="/usr/local /usr"     # you might want to change this
  dnl SEARCH_FOR="/include/httpparser.h"  # you most likely want to change this
  dnl if test -r $PHP_httpparser/$SEARCH_FOR; then # path given as parameter
  dnl   httpparser_DIR=$PHP_httpparser
  dnl else # search default path list
  dnl   AC_MSG_CHECKING([for httpparser files in default path])
  dnl   for i in $SEARCH_PATH ; do
  dnl     if test -r $i/$SEARCH_FOR; then
  dnl       httpparser_DIR=$i
  dnl       AC_MSG_RESULT(found in $i)
  dnl     fi
  dnl   done
  dnl fi
  dnl
  dnl if test -z "$httpparser_DIR"; then
  dnl   AC_MSG_RESULT([not found])
  dnl   AC_MSG_ERROR([Please reinstall the httpparser distribution])
  dnl fi

  dnl # --with-httpparser -> add include path
  dnl PHP_ADD_INCLUDE($httpparser_DIR/include)

  dnl # --with-httpparser -> check for lib and symbol presence
  dnl LIBNAME=httpparser # you may want to change this
  dnl LIBSYMBOL=httpparser # you most likely want to change this 

  dnl PHP_CHECK_LIBRARY($LIBNAME,$LIBSYMBOL,
  dnl [
  dnl   PHP_ADD_LIBRARY_WITH_PATH($LIBNAME, $httpparser_DIR/lib, httpparser_SHARED_LIBADD)
  dnl   AC_DEFINE(HAVE_httpparserLIB,1,[ ])
  dnl ],[
  dnl   AC_MSG_ERROR([wrong httpparser lib version or lib not found])
  dnl ],[
  dnl   -L$httpparser_DIR/lib -lm
  dnl ])
  dnl
  dnl PHP_SUBST(httpparser_SHARED_LIBADD)

  dnl if test "$PHP_DEBUG" != "no"; then
    dnl OPT=-O0 -g -Wall -Wextra -Werror -Ihttp_parser/
  dnl else 
    dnl OPT_FAST=-O3 -DHTTP_PARSER_STRICT=0 -Ihttp_parser/
  dnl fi

  PHP_ADD_INCLUDE(http-parser)


  PHP_NEW_EXTENSION(httpparser, main.c callback.c http-parser/http_parser.c, $ext_shared)
fi
