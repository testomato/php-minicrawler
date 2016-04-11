PHP_ARG_WITH(minicrawler, for minicrawler support,
Make sure that the comment is aligned:
[  --with-minicrawler             Include minicrawler support])

if test "$PHP_MINICRAWLER" != "no"; then
  AC_DEFINE(HAVE_MINICRAWLER, 1, [ ])

  PHP_CHECK_LIBRARY([minicrawler-4], [mcrawler_go],
  [
	PHP_EVAL_INCLINE(`pkg-config --cflags-only-I libminicrawler-4`)
	PHP_EVAL_LIBLINE(`pkg-config --libs libminicrawler-4`, MINICRAWLER_SHARED_LIBADD)
    AC_DEFINE(HAVE_MINICRAWLERLIB, 1, [ ])
  ],[
    AC_MSG_ERROR([wrong libminicrawler-4 version or lib not found])
  ],[
    -L/usr/lib -lm
  ])
  
  PHP_SUBST(MINICRAWLER_SHARED_LIBADD)

  PHP_NEW_EXTENSION(minicrawler, minicrawler.c, $ext_shared)
fi

AC_PROG_CC_C99
if test "${ac_cv_prog_cc_c99}" = "no"; then
    AC_MSG_ERROR([your compiler does not support ISO Standard C 99])
fi
