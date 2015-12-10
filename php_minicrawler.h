#ifndef PHP_MINICRAWLER_H
#define PHP_MINICRAWLER_H 1
#define PHP_MINICRAWLER_VERSION "1.0"
#define PHP_MINICRAWLER_EXTNAME "minicrawler"
#define MINICRAWLER_WORLD_EXTNAME "minicrawler"

#include <minicrawler/minicrawler.h>

#define MCRAWLER_URL_RES_NAME "minicrawler URL"
#define MCRAWLER_SETTINGS_RES_NAME "minicrawler settings"

PHP_MINIT_FUNCTION(minicrawler);

PHP_FUNCTION(mcrawler_init_url);
PHP_FUNCTION(mcrawler_init_settings);
PHP_FUNCTION(mcrawler_close_url);
PHP_FUNCTION(mcrawler_close_settings);
PHP_FUNCTION(mcrawler_get_timeout);
PHP_FUNCTION(mcrawler_get_delay);
PHP_FUNCTION(mcrawler_set_useragent);
PHP_FUNCTION(mcrawler_set_headers);
PHP_FUNCTION(mcrawler_set_credentials);
PHP_FUNCTION(mcrawler_set_postdata);
PHP_FUNCTION(mcrawler_set_options);
PHP_FUNCTION(mcrawler_set_option);
PHP_FUNCTION(mcrawler_set_cookies);
PHP_FUNCTION(mcrawler_go);
PHP_FUNCTION(mcrawler_get_index);
PHP_FUNCTION(mcrawler_get_state);
PHP_FUNCTION(mcrawler_get_status);
PHP_FUNCTION(mcrawler_get_url);
PHP_FUNCTION(mcrawler_get_method);
PHP_FUNCTION(mcrawler_get_request);
PHP_FUNCTION(mcrawler_get_redirected_to);
PHP_FUNCTION(mcrawler_get_header);
PHP_FUNCTION(mcrawler_get_body);
PHP_FUNCTION(mcrawler_get_response_size);
PHP_FUNCTION(mcrawler_get_status);
PHP_FUNCTION(mcrawler_get_url);
PHP_FUNCTION(mcrawler_get_timing);
PHP_FUNCTION(mcrawler_get_cookies);
PHP_FUNCTION(mcrawler_serialize);
PHP_FUNCTION(mcrawler_unserialize);
PHP_FUNCTION(mcrawler_version);

typedef struct {
	long id;
	void ***thread_ctx;
} php_mcrawler_ctx;

extern zend_module_entry minicrawler_module_entry;
#define phpext_minicrawler_ptr &minicrawler_module_entry

#endif
