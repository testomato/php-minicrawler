#ifndef PHP_MINICRAWLER_H
#define PHP_MINICRAWLER_H 1
#define PHP_MINICRAWLER_VERSION "1.0"
#define PHP_MINICRAWLER_EXTNAME "minicrawler"
#define MINICRAWLER_WORLD_EXTNAME "minicrawler"

#include <minicrawler/minicrawler.h>

#define MCRAWLER_URL_RES_NAME "Minicrawler URL"
#define MCRAWLER_SETTINGS_RES_NAME "Minicrawler Settings"

PHP_MINIT_FUNCTION(minicrawler);

PHP_FUNCTION(mcrawler_init_url);
PHP_FUNCTION(mcrawler_init_settings);
PHP_FUNCTION(mcrawler_go);
PHP_FUNCTION(mcrawler_get_status);
PHP_FUNCTION(mcrawler_get_url);
PHP_FUNCTION(mcrawler_get_timing);

extern zend_module_entry minicrawler_module_entry;
#define phpext_minicrawler_ptr &minicrawler_module_entry

#endif
