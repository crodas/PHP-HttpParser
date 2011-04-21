dnl $Id$
dnl config.m4 for extension webserver

dnl Comments in this file start with the string 'dnl'.
dnl Remove where necessary. This file will not work
dnl without editing.

dnl If your extension references something external, use with:

dnl PHP_ARG_WITH(webserver, for webserver support,
dnl Make sure that the comment is aligned:
dnl [  --with-webserver             Include webserver support])

dnl Otherwise use enable:

dnl PHP_ARG_ENABLE(webserver, whether to enable webserver support,
dnl Make sure that the comment is aligned:
dnl [  --enable-webserver           Enable webserver support])

if test "$PHP_WEBSERVER" != "no"; then
  dnl Write more examples of tests here...

  dnl # --with-webserver -> check with-path
  dnl SEARCH_PATH="/usr/local /usr"     # you might want to change this
  dnl SEARCH_FOR="/include/webserver.h"  # you most likely want to change this
  dnl if test -r $PHP_WEBSERVER/$SEARCH_FOR; then # path given as parameter
  dnl   WEBSERVER_DIR=$PHP_WEBSERVER
  dnl else # search default path list
  dnl   AC_MSG_CHECKING([for webserver files in default path])
  dnl   for i in $SEARCH_PATH ; do
  dnl     if test -r $i/$SEARCH_FOR; then
  dnl       WEBSERVER_DIR=$i
  dnl       AC_MSG_RESULT(found in $i)
  dnl     fi
  dnl   done
  dnl fi
  dnl
  dnl if test -z "$WEBSERVER_DIR"; then
  dnl   AC_MSG_RESULT([not found])
  dnl   AC_MSG_ERROR([Please reinstall the webserver distribution])
  dnl fi

  dnl # --with-webserver -> add include path
  dnl PHP_ADD_INCLUDE($WEBSERVER_DIR/include)

  dnl # --with-webserver -> check for lib and symbol presence
  dnl LIBNAME=webserver # you may want to change this
  dnl LIBSYMBOL=webserver # you most likely want to change this 

  dnl PHP_CHECK_LIBRARY($LIBNAME,$LIBSYMBOL,
  dnl [
  dnl   PHP_ADD_LIBRARY_WITH_PATH($LIBNAME, $WEBSERVER_DIR/lib, WEBSERVER_SHARED_LIBADD)
  dnl   AC_DEFINE(HAVE_WEBSERVERLIB,1,[ ])
  dnl ],[
  dnl   AC_MSG_ERROR([wrong webserver lib version or lib not found])
  dnl ],[
  dnl   -L$WEBSERVER_DIR/lib -lm
  dnl ])
  dnl
  dnl PHP_SUBST(WEBSERVER_SHARED_LIBADD)

  PHP_NEW_EXTENSION(webserver, webserver.c, $ext_shared)
fi
