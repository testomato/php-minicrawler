#ifndef PHP_MINICRAWLER_H
#define PHP_MINICRAWLER_H 1
#define PHP_MINICRAWLER_VERSION "1.0"
#define PHP_MINICRAWLER_EXTNAME "minicrawler"
#define MINICRAWLER_WORLD_EXTNAME "minicrawler"

PHP_FUNCTION(minicrawler);

extern zend_module_entry minicrawler_module_entry;
#define phpext_minicrawler_ptr &minicrawler_module_entry

#endif
