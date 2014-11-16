PHP_ARG_ENABLE(minicrawler, whether to enable minicrawler support,
[ --enable-minicrawler   Enable minicrawler support])
if test "$PHP_MINICRAWLER" = "yes"; then
  AC_DEFINE(HAVE_MINICRAWLER, 1, [Whether you have Minicrawler])
  PHP_NEW_EXTENSION(minicrawler, minicrawler.c, $ext_shared)
fi
