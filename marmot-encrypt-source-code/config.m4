dnl $Id$
dnl config.m4 for extension marmot

dnl Comments in this file start with the string 'dnl'.
dnl Remove where necessary. This file will not work
dnl without editing.

dnl If your extension references something external, use with:

PHP_ARG_WITH(marmot, for marmot support,
dnl Make sure that the comment is aligned:
[  --with-marmot             Include marmot support])

dnl Otherwise use enable:

dnl PHP_ARG_ENABLE(marmot, whether to enable marmot support,
dnl Make sure that the comment is aligned:
dnl [  --enable-marmot           Enable marmot support])

if test "$PHP_MARMOT" != "no"; then
  dnl Write more examples of tests here...

  dnl # --with-marmot -> check with-path
  dnl SEARCH_PATH="/usr/local /usr"     # you might want to change this
  dnl SEARCH_FOR="/include/marmot.h"  # you most likely want to change this
  dnl if test -r $PHP_MARMOT/$SEARCH_FOR; then # path given as parameter
  dnl   MARMOT_DIR=$PHP_MARMOT
  dnl else # search default path list
  dnl   AC_MSG_CHECKING([for marmot files in default path])
  dnl   for i in $SEARCH_PATH ; do
  dnl     if test -r $i/$SEARCH_FOR; then
  dnl       MARMOT_DIR=$i
  dnl       AC_MSG_RESULT(found in $i)
  dnl     fi
  dnl   done
  dnl fi
  dnl
  dnl if test -z "$MARMOT_DIR"; then
  dnl   AC_MSG_RESULT([not found])
  dnl   AC_MSG_ERROR([Please reinstall the marmot distribution])
  dnl fi

  dnl # --with-marmot -> add include path
  dnl PHP_ADD_INCLUDE($MARMOT_DIR/include)

  dnl # --with-marmot -> check for lib and symbol presence
  dnl LIBNAME=marmot # you may want to change this
  dnl LIBSYMBOL=marmot # you most likely want to change this 

  dnl PHP_CHECK_LIBRARY($LIBNAME,$LIBSYMBOL,
  dnl [
  dnl   PHP_ADD_LIBRARY_WITH_PATH($LIBNAME, $MARMOT_DIR/$PHP_LIBDIR, MARMOT_SHARED_LIBADD)
  dnl   AC_DEFINE(HAVE_MARMOTLIB,1,[ ])
  dnl ],[
  dnl   AC_MSG_ERROR([wrong marmot lib version or lib not found])
  dnl ],[
  dnl   -L$MARMOT_DIR/$PHP_LIBDIR -lm
  dnl ])
  dnl
  dnl PHP_SUBST(MARMOT_SHARED_LIBADD)

  PHP_NEW_EXTENSION(marmot, marmot.c, $ext_shared,, -DZEND_ENABLE_STATIC_TSRMLS_CACHE=1)
fi
