#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include "php.h"
#include "php_minicrawler.h"

static zend_function_entry minicrawler_functions[] = {
    PHP_FE(minicrawler, NULL)
    {NULL, NULL, NULL}
};

zend_module_entry minicrawler_module_entry = {
    STANDARD_MODULE_HEADER,
    MINICRAWLER_WORLD_EXTNAME,
    minicrawler_functions,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    PHP_MINICRAWLER_VERSION,
    STANDARD_MODULE_PROPERTIES
};

#ifdef COMPILE_DL_MINICRAWLER
ZEND_GET_MODULE(minicrawler)
#endif

PHP_FUNCTION(minicrawler)
{
    RETURN_STRING("Minicrawler", 1);
}
