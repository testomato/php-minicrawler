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
    PHP_FE(mcrawler_close_url, NULL)
    PHP_FE(mcrawler_close_settings, NULL)
    PHP_FE(mcrawler_set_useragent, NULL)
    PHP_FE(mcrawler_set_headers, NULL)
    PHP_FE(mcrawler_set_credentials, NULL)
    PHP_FE(mcrawler_set_postdata, NULL)
    PHP_FE(mcrawler_go, NULL)
    PHP_FE(mcrawler_get_status, NULL)
    PHP_FE(mcrawler_get_url, NULL)
    PHP_FE(mcrawler_get_timing, NULL)
    PHP_FE(mcrawler_version, NULL)
    PHP_FE_END
};

zend_module_entry minicrawler_module_entry = {
    STANDARD_MODULE_HEADER,
    MINICRAWLER_WORLD_EXTNAME,
    minicrawler_functions,
    PHP_MINIT(minicrawler),
    NULL,//PHP_MSHUTDOWN(minicrawler)
    NULL,
    NULL,
    NULL,//PHP_MINFO(minicrawler)
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
		efree(url->userdata);
		efree(url);
		//TODO, uvolnit vše
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
	le_mcrawler_url = zend_register_list_destructors_ex(mcrawler_url_dtor, NULL, MCRAWLER_URL_RES_NAME, module_number);
	le_mcrawler_settings = zend_register_list_destructors_ex(mcrawler_settings_dtor, NULL, MCRAWLER_SETTINGS_RES_NAME, module_number);
}

PHP_FUNCTION(mcrawler_init_url)
{
    mcrawler_url *url;
	php_mcrawler_ctx *ctx;
	char *url_s, *method_s = NULL;
	int url_len, method_len = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s|s", &url_s, &url_len, &method_s, &method_len) == FAILURE) {
		RETURN_FALSE;
	}

	url = emalloc(sizeof(mcrawler_url));
	memset(url, 0, sizeof(mcrawler_url));

	ctx = (php_mcrawler_ctx *)emalloc(sizeof(php_mcrawler_ctx));
	url->userdata = ctx;
	mcrawler_init_url(url, url_s);
	if (method_s) {
		strncpy(url->method, method_s, sizeof(url->method) - 1);
	} else {
		strcpy(url->method, "GET");
	}

	ZEND_REGISTER_RESOURCE(return_value, url, le_mcrawler_url);
	ctx->id = Z_LVAL_P(return_value);
}

PHP_FUNCTION(mcrawler_close_url)
{
	zval *zurl;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "r", &zurl) == FAILURE) {
		RETURN_FALSE;
	}

	zend_list_delete(Z_LVAL_P(zurl));
	RETURN_TRUE;
}

PHP_FUNCTION(mcrawler_init_settings)
{
	mcrawler_settings *settings;
	long timeout = 5, delay = 100;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "|ll", &timeout, &delay) == FAILURE) {
		RETURN_FALSE;
	}

	settings = emalloc(sizeof(mcrawler_settings));
	mcrawler_init_settings(settings);
	settings->timeout = timeout;
	settings->delay = delay;

	ZEND_REGISTER_RESOURCE(return_value, settings, le_mcrawler_settings);
}

PHP_FUNCTION(mcrawler_close_settings)
{
	zval *zsetting;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "r", &zsetting) == FAILURE) {
		RETURN_FALSE;
	}

	zend_list_delete(Z_LVAL_P(zsetting));
	RETURN_TRUE;
}

PHP_FUNCTION(mcrawler_set_useragent)
{
	mcrawler_url *url;
	zval *zurl;
	char *useragent;
	int useragent_len;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "rs", &zurl, &useragent, &useragent_len) == FAILURE) {
		RETURN_FALSE;
	}
	ZEND_FETCH_RESOURCE(url, mcrawler_url*, &zurl, -1, MCRAWLER_URL_RES_NAME, le_mcrawler_url);

	strncpy(url->customagent, useragent, sizeof(url->customagent) - 1);
	RETURN_TRUE;
}

PHP_FUNCTION(mcrawler_set_headers)
{
	mcrawler_url *url;
	zval *zurl;
	char *headers;
	int headers_len;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "rs", &zurl, &headers, &headers_len) == FAILURE) {
		RETURN_FALSE;
	}
	ZEND_FETCH_RESOURCE(url, mcrawler_url*, &zurl, -1, MCRAWLER_URL_RES_NAME, le_mcrawler_url);

	strncpy(url->customheader, headers, sizeof(url->customheader) - 1);
	RETURN_TRUE;
}

PHP_FUNCTION(mcrawler_set_credentials)
{
	mcrawler_url *url;
	zval *zurl;
	char *username, *password;
	int username_len, password_len;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "rss", &zurl, &username, &username_len, &password, &password_len) == FAILURE) {
		RETURN_FALSE;
	}
	ZEND_FETCH_RESOURCE(url, mcrawler_url*, &zurl, -1, MCRAWLER_URL_RES_NAME, le_mcrawler_url);

	strncpy(url->username, username, sizeof(url->username) - 1);
	strncpy(url->password, password, sizeof(url->password) - 1);
	RETURN_TRUE;
}

PHP_FUNCTION(mcrawler_set_postdata)
{
	mcrawler_url *url;
	zval *zurl;
	char *postdata;
	int postdata_len;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "rs", &zurl, &postdata, &postdata_len) == FAILURE) {
		RETURN_FALSE;
	}
	ZEND_FETCH_RESOURCE(url, mcrawler_url*, &zurl, -1, MCRAWLER_URL_RES_NAME, le_mcrawler_url);

	url->post = malloc(postdata_len);
	url->postlen = postdata_len;
	memcpy(url->post, postdata, postdata_len);
	RETURN_TRUE;
}

struct fcall {
	zend_fcall_info info;
	zend_fcall_info_cache info_cache;
};

static void callback(mcrawler_url* url, void *arg) {
	struct fcall *fc = (struct fcall *)arg;
	php_mcrawler_ctx *ctx = (php_mcrawler_ctx *)url->userdata;
	/** php 7
	zval args[1];
	zval retval;
	*/
	zval *zurl = NULL;
	zval **args[1];
	zval *retval = NULL;

	// nejde použí zend_register_resource, protože by dvě různé resource měli stejný pointer
	MAKE_STD_ZVAL(zurl);
	ZVAL_RESOURCE(zurl, ctx->id);
	zend_list_addref(ctx->id);
	args[0] = &zurl;

	fc->info.no_separation = 0;
	fc->info.param_count = 1;
	/** php 7 
	fc->info.params = args;
	fc->info.retval = &retval;
	**/
	fc->info.params = args;
	fc->info.retval_ptr_ptr = &retval;
	if (zend_call_function(&fc->info, &fc->info_cache TSRMLS_CC) == SUCCESS) {
		if (retval) {
			zval_ptr_dtor(&retval);
		}
	}
	zval_ptr_dtor(args[0]);
}

PHP_FUNCTION(mcrawler_go)
{
	mcrawler_settings *settings;
	zval *zurls, *zsettings, **zurl;
	struct fcall fc;

	fc.info = empty_fcall_info;
	fc.info_cache = empty_fcall_info_cache;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "ar|f", &zurls, &zsettings, &fc.info, &fc.info_cache) == FAILURE) {
		RETURN_FALSE;
	}

	HashTable *arr_hash = Z_ARRVAL_P(zurls);
	HashPosition pointer;
	mcrawler_url *urls[zend_hash_num_elements(arr_hash) + 1];
	int i = 0;

	for(zend_hash_internal_pointer_reset_ex(arr_hash, &pointer); zend_hash_get_current_data_ex(arr_hash, (void**) &zurl, &pointer) == SUCCESS; zend_hash_move_forward_ex(arr_hash, &pointer)) {
		ZEND_FETCH_RESOURCE(urls[i], mcrawler_url*, zurl, -1, MCRAWLER_URL_RES_NAME, le_mcrawler_url);
		i++;
	}
	urls[i] = NULL;

	ZEND_FETCH_RESOURCE(settings, mcrawler_settings*, &zsettings, -1, MCRAWLER_SETTINGS_RES_NAME, le_mcrawler_settings);

	mcrawler_go(urls, settings, callback, (void *)&fc);

	RETURN_TRUE;
}

PHP_FUNCTION(mcrawler_get_status)
{
	mcrawler_url *url;
	zval *zurl;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "r", &zurl) == FAILURE) {
		RETURN_FALSE;
	}
	ZEND_FETCH_RESOURCE(url, mcrawler_url*, &zurl, -1, MCRAWLER_URL_RES_NAME, le_mcrawler_url);

	RETURN_LONG(url->status);
}

PHP_FUNCTION(mcrawler_get_url)
{
	mcrawler_url *url;
	zval *zurl;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "r", &zurl) == FAILURE) {
		RETURN_FALSE;
	}
	ZEND_FETCH_RESOURCE(url, mcrawler_url*, &zurl, -1, MCRAWLER_URL_RES_NAME, le_mcrawler_url);

	RETURN_STRING(url->rawurl, 1);
}

PHP_FUNCTION(mcrawler_get_timing)
{
	mcrawler_url *url;
	zval *zurl;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "r", &zurl) == FAILURE) {
		RETURN_FALSE;
	}
	ZEND_FETCH_RESOURCE(url, mcrawler_url*, &zurl, -1, MCRAWLER_URL_RES_NAME, le_mcrawler_url);

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

PHP_FUNCTION(mcrawler_version)
{
	RETURN_STRING(mcrawler_version(), 1);
}
