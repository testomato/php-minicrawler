#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include "php.h"
#include "php_minicrawler.h"

int le_mcrawler_url;
int le_mcrawler_settings;

static zend_function_entry minicrawler_functions[] = {
    PHP_FE(mcrawler_init_url, NULL)
    PHP_FE(mcrawler_init_settings, NULL)
    PHP_FE(mcrawler_go, NULL)
    PHP_FE(mcrawler_get_status, NULL)
    PHP_FE(mcrawler_get_url, NULL)
    PHP_FE(mcrawler_get_timing, NULL)
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

static void mcrawler_url_dtor(zend_rsrc_list_entry *rsrc TSRMLS_DC)
{
	mcrawler_url *url = (mcrawler_url *)rsrc->ptr;
	if (url) {
		//TODO, uvolnit vše
		efree(url);
	}
}

static void mcrawler_settings_dtor(zend_rsrc_list_entry *rsrc TSRMLS_DC)
{
	mcrawler_settings *settings = (mcrawler_settings *)rsrc->ptr;
	if (settings) {
		efree(settings);
	}
}

PHP_MINIT_FUNCTION(minicrawler)
{
	le_mcrawler_url = zend_register_list_destructors_ex(mcrawler_url_dtor, NULL, PHP_MCRAWLER_URL_RES_NAME, module_number);
	le_mcrawler_settings = zend_register_list_destructors_ex(mcrawler_settings_dtor, NULL, PHP_MCRAWLER_SETTINGS_RES_NAME, module_number);
}

PHP_FUNCTION(mcrawler_init_url)
{
    mcrawler_url *url;
	char *url_s;
	int url_len;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &url_s, &url_len) == FAILURE) {
		RETURN_FALSE;
	}

	url = emalloc(sizeof(mcrawler_url));
	memset(url, 0, sizeof(mcrawler_url));
	mcrawler_init_url(url, url_s);
	strcpy(url->method, "GET");

	ZEND_REGISTER_RESOURCE(return_value, url, le_mcrawler_url);
}

PHP_FUNCTION(mcrawler_init_settings)
{
	mcrawler_settings *settings;

	settings = emalloc(sizeof(mcrawler_settings));
	memset(settings, 0, sizeof(settings));
	mcrawler_init_settings(settings);

	ZEND_REGISTER_RESOURCE(return_value, settings, le_mcrawler_settings);
}

static void callback(mcrawler_url* url, void *arg) {}

PHP_FUNCTION(mcrawler_go)
{
	mcrawler_settings *settings;
	zval *zurls, *zsettings, **zurl;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "ar", &zurls, &zsettings) == FAILURE) {
		RETURN_FALSE;
	}

	HashTable *arr_hash = Z_ARRVAL_P(zurls);
	HashPosition pointer;
	mcrawler_url *urls[zend_hash_num_elements(arr_hash) + 1];
	int i = 0;

	for(zend_hash_internal_pointer_reset_ex(arr_hash, &pointer); zend_hash_get_current_data_ex(arr_hash, (void**) &zurl, &pointer) == SUCCESS; zend_hash_move_forward_ex(arr_hash, &pointer)) {
		ZEND_FETCH_RESOURCE(urls[i], mcrawler_url*, zurl, -1, PHP_MCRAWLER_URL_RES_NAME, le_mcrawler_url);
		i++;
	}
	urls[i] = NULL;

	ZEND_FETCH_RESOURCE(settings, mcrawler_settings*, &zsettings, -1, PHP_MCRAWLER_SETTINGS_RES_NAME, le_mcrawler_settings);

	mcrawler_go(urls, settings, callback, NULL);

	RETURN_TRUE;
}

PHP_FUNCTION(mcrawler_get_status)
{
	mcrawler_url *url;
	zval *zurl;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "r", &zurl) == FAILURE) {
		RETURN_FALSE;
	}
	ZEND_FETCH_RESOURCE(url, mcrawler_url*, &zurl, -1, PHP_MCRAWLER_URL_RES_NAME, le_mcrawler_url);

	RETURN_LONG(url->status);
}

PHP_FUNCTION(mcrawler_get_url)
{
	mcrawler_url *url;
	zval *zurl;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "r", &zurl) == FAILURE) {
		RETURN_FALSE;
	}
	ZEND_FETCH_RESOURCE(url, mcrawler_url*, &zurl, -1, PHP_MCRAWLER_URL_RES_NAME, le_mcrawler_url);

	RETURN_STRING(url->rawurl, 1);
}

PHP_FUNCTION(mcrawler_get_timing)
{
	mcrawler_url *url;
	zval *zurl;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "r", &zurl) == FAILURE) {
		RETURN_FALSE;
	}
	ZEND_FETCH_RESOURCE(url, mcrawler_url*, &zurl, -1, PHP_MCRAWLER_URL_RES_NAME, le_mcrawler_url);

	array_init(return_value);
	mcrawler_timing *timing = &url->timing;
	zval *timingArray;

	if (timing->dnsstart) {
		ALLOC_INIT_ZVAL(timingArray);
		array_init(timingArray);
		add_assoc_string(timingArray, "metric", "DNS Lookup", 1);
		add_assoc_long(timingArray, "value", (timing->dnsend ? timing->dnsend : timing->done) - timing->dnsstart);
		add_next_index_zval(return_value, timingArray);
	}

	if (timing->connectionstart) {
		ALLOC_INIT_ZVAL(timingArray);
		array_init(timingArray);
		add_assoc_string(timingArray, "metric", "Initial connection", 1);
		add_assoc_long(timingArray, "value", (timing->requeststart ? timing->requeststart : timing->done) - timing->connectionstart);
		add_next_index_zval(return_value, timingArray);
	}

	if (timing->sslstart) {
		ALLOC_INIT_ZVAL(timingArray);
		array_init(timingArray);
		add_assoc_string(timingArray, "metric", "SSL", 1);
		add_assoc_long(timingArray, "value", (timing->sslend ? timing->sslend : timing->done) - timing->sslstart);
		add_next_index_zval(return_value, timingArray);
	}

	if (timing->requeststart) {
		ALLOC_INIT_ZVAL(timingArray);
		array_init(timingArray);
		add_assoc_string(timingArray, "metric", "Request", 1);
		add_assoc_long(timingArray, "value", (timing->requestend ? timing->requestend : timing->done) - timing->requeststart);
		add_next_index_zval(return_value, timingArray);
	}

	if (timing->requestend) {
		ALLOC_INIT_ZVAL(timingArray);
		array_init(timingArray);
		add_assoc_string(timingArray, "metric", "Waiting", 1);
		add_assoc_long(timingArray, "value", (timing->firstbyte ? timing->firstbyte : timing->done) - timing->requestend);
		add_next_index_zval(return_value, timingArray);
	}

	if (timing->firstbyte) {
		ALLOC_INIT_ZVAL(timingArray);
		array_init(timingArray);
		add_assoc_string(timingArray, "metric", "Content download", 1);
		add_assoc_long(timingArray, "value", (timing->lastread ? timing->lastread : timing->done) - timing->firstbyte);
		add_next_index_zval(return_value, timingArray);
	}

	if (timing->connectionstart) {
		ALLOC_INIT_ZVAL(timingArray);
		array_init(timingArray);
		add_assoc_string(timingArray, "metric", "Total", 1);
		add_assoc_long(timingArray, "value", (timing->lastread ? timing->lastread : timing->done) - timing->connectionstart);
		add_next_index_zval(return_value, timingArray);
	}
}
