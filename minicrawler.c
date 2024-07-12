#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include "php.h"
#include "php_minicrawler.h"
#include "zend_exceptions.h"

int le_mcrawler_url;
int le_mcrawler_settings;
int le_mcrawler_url_url;

ZEND_BEGIN_ARG_INFO(arginfo_mcrawler_init_url, 0)
ZEND_ARG_TYPE_INFO(0, url, IS_STRING, 0)
ZEND_ARG_TYPE_INFO(0, method, IS_STRING, 1)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(arginfo_mcrawler_init_settings, 0)
ZEND_ARG_TYPE_INFO(0, timeout, IS_LONG, 1)
ZEND_ARG_TYPE_INFO(0, delay, IS_LONG, 1)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(arginfo_mcrawler_close_url, 0)
ZEND_ARG_INFO(0, url)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(arginfo_mcrawler_close_settings, 0)
ZEND_ARG_INFO(0, settings)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(arginfo_mcrawler_get_timeout, 0)
ZEND_ARG_INFO(0, settings)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(arginfo_mcrawler_get_delay, 0)
ZEND_ARG_INFO(0, settings)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(arginfo_mcrawler_set_useragent, 0)
ZEND_ARG_INFO(0, url)
ZEND_ARG_TYPE_INFO(0, useragent, IS_STRING, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(arginfo_mcrawler_set_headers, 0)
ZEND_ARG_INFO(0, url)
ZEND_ARG_TYPE_INFO(0, headers, IS_STRING, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(arginfo_mcrawler_add_headers, 0)
ZEND_ARG_INFO(0, url)
ZEND_ARG_TYPE_INFO(0, headers, IS_STRING, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(arginfo_mcrawler_set_credentials, 0)
ZEND_ARG_INFO(0, url)
ZEND_ARG_TYPE_INFO(0, username, IS_STRING, 0)
ZEND_ARG_TYPE_INFO(0, password, IS_STRING, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(arginfo_mcrawler_set_postdata, 0)
ZEND_ARG_INFO(0, url)
ZEND_ARG_TYPE_INFO(0, postdata, IS_STRING, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(arginfo_mcrawler_set_options, 0)
ZEND_ARG_INFO(0, url)
ZEND_ARG_TYPE_INFO(0, options, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(arginfo_mcrawler_set_option, 0)
ZEND_ARG_INFO(0, url)
ZEND_ARG_TYPE_INFO(0, option, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(arginfo_mcrawler_set_cookies, 0)
ZEND_ARG_INFO(0, url)
ZEND_ARG_TYPE_INFO(0, cookies, IS_STRING, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(arginfo_mcrawler_add_cookies, 0)
ZEND_ARG_INFO(0, url)
ZEND_ARG_TYPE_INFO(0, cookies, IS_STRING, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(arginfo_mcrawler_go, 0)
ZEND_ARG_TYPE_INFO(0, urls, IS_ARRAY, 0)
ZEND_ARG_INFO(0, settings)
ZEND_ARG_INFO(0, callback)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(arginfo_mcrawler_reset, 0)
ZEND_ARG_INFO(0, url)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(arginfo_mcrawler_get_index, 0)
ZEND_ARG_INFO(0, url)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(arginfo_mcrawler_get_state, 0)
ZEND_ARG_INFO(0, url)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(arginfo_mcrawler_get_status, 0)
ZEND_ARG_INFO(0, url)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(arginfo_mcrawler_get_url, 0)
ZEND_ARG_INFO(0, url)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(arginfo_mcrawler_get_method, 0)
ZEND_ARG_INFO(0, url)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(arginfo_mcrawler_get_request, 0)
ZEND_ARG_INFO(0, url)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(arginfo_mcrawler_get_redirected_to, 0)
ZEND_ARG_INFO(0, url)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(arginfo_mcrawler_get_redirect_info, 0)
ZEND_ARG_INFO(0, url)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(arginfo_mcrawler_get_header, 0)
ZEND_ARG_INFO(0, url)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(arginfo_mcrawler_get_body, 0)
ZEND_ARG_INFO(0, url)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(arginfo_mcrawler_get_response_size, 0)
ZEND_ARG_INFO(0, url)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(arginfo_mcrawler_get_options, 0)
ZEND_ARG_INFO(0, url)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(arginfo_mcrawler_get_timing, 0)
ZEND_ARG_INFO(0, url)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(arginfo_mcrawler_get_cookies, 0)
ZEND_ARG_INFO(0, url)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(arginfo_mcrawler_get_content_type, 0)
ZEND_ARG_INFO(0, url)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(arginfo_mcrawler_get_charset, 0)
ZEND_ARG_INFO(0, url)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(arginfo_mcrawler_get_www_authenticate, 0)
ZEND_ARG_INFO(0, url)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(arginfo_mcrawler_get_error_msg, 0)
ZEND_ARG_INFO(0, url)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(arginfo_mcrawler_serialize, 0)
ZEND_ARG_TYPE_INFO(0, urls, IS_ARRAY, 0)
ZEND_ARG_INFO(0, settings)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(arginfo_mcrawler_unserialize, 0)
ZEND_ARG_TYPE_INFO(0, serialized_data, IS_STRING, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(arginfo_mcrawler_version, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(arginfo_mcrawler_parse_url, 0)
ZEND_ARG_TYPE_INFO(0, url, IS_STRING, 0)
ZEND_ARG_INFO(0, base_url)
ZEND_END_ARG_INFO()


static zend_function_entry minicrawler_functions[] = {
    PHP_FE(mcrawler_init_url, arginfo_mcrawler_init_url)
    PHP_FE(mcrawler_init_settings, arginfo_mcrawler_init_settings)
    PHP_FE(mcrawler_close_url, arginfo_mcrawler_close_url)
    PHP_FE(mcrawler_close_settings, arginfo_mcrawler_close_settings)
    PHP_FE(mcrawler_get_timeout, arginfo_mcrawler_get_timeout)
    PHP_FE(mcrawler_get_delay, arginfo_mcrawler_get_delay)
    PHP_FE(mcrawler_set_useragent, arginfo_mcrawler_set_useragent)
    PHP_FE(mcrawler_set_headers, arginfo_mcrawler_set_headers)
    PHP_FE(mcrawler_add_headers, arginfo_mcrawler_add_headers)
    PHP_FE(mcrawler_set_credentials, arginfo_mcrawler_set_credentials)
    PHP_FE(mcrawler_set_postdata, arginfo_mcrawler_set_postdata)
    PHP_FE(mcrawler_set_options, arginfo_mcrawler_set_options)
    PHP_FE(mcrawler_set_option, arginfo_mcrawler_set_option)
    PHP_FE(mcrawler_set_cookies, arginfo_mcrawler_set_cookies)
    PHP_FE(mcrawler_add_cookies, arginfo_mcrawler_add_cookies)
    PHP_FE(mcrawler_go, arginfo_mcrawler_go)
    PHP_FE(mcrawler_reset, arginfo_mcrawler_reset)
    PHP_FE(mcrawler_get_index, arginfo_mcrawler_get_index)
    PHP_FE(mcrawler_get_state, arginfo_mcrawler_get_state)
    PHP_FE(mcrawler_get_status, arginfo_mcrawler_get_status)
    PHP_FE(mcrawler_get_url, arginfo_mcrawler_get_url)
    PHP_FE(mcrawler_get_method, arginfo_mcrawler_get_method)
    PHP_FE(mcrawler_get_request, arginfo_mcrawler_get_request)
    PHP_FE(mcrawler_get_redirected_to, arginfo_mcrawler_get_redirected_to)
    PHP_FE(mcrawler_get_redirect_info, arginfo_mcrawler_get_redirect_info)
    PHP_FE(mcrawler_get_header, arginfo_mcrawler_get_header)
    PHP_FE(mcrawler_get_body, arginfo_mcrawler_get_body)
    PHP_FE(mcrawler_get_response_size, arginfo_mcrawler_get_response_size)
    PHP_FE(mcrawler_get_options, arginfo_mcrawler_get_options)
    PHP_FE(mcrawler_get_timing, arginfo_mcrawler_get_timing)
    PHP_FE(mcrawler_get_cookies, arginfo_mcrawler_get_cookies)
    PHP_FE(mcrawler_get_content_type, arginfo_mcrawler_get_content_type)
    PHP_FE(mcrawler_get_charset, arginfo_mcrawler_get_charset)
    PHP_FE(mcrawler_get_www_authenticate, arginfo_mcrawler_get_www_authenticate)
    PHP_FE(mcrawler_get_error_msg, arginfo_mcrawler_get_error_msg)
    PHP_FE(mcrawler_serialize, arginfo_mcrawler_serialize)
    PHP_FE(mcrawler_unserialize, arginfo_mcrawler_unserialize)
    PHP_FE(mcrawler_version, arginfo_mcrawler_version)
    PHP_FE(mcrawler_parse_url, arginfo_mcrawler_parse_url)
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

static zend_class_entry *php_mcrawler_exception_ce, *php_mcrawler_url_exception_ce;

#ifdef COMPILE_DL_MINICRAWLER
ZEND_GET_MODULE(minicrawler)
#endif

static void mcrawler_url_dtor(zend_resource *rsrc)
{
	mcrawler_url *url = (mcrawler_url *)rsrc->ptr;
	if (url) {
		efree(url->userdata);
		mcrawler_free_url(url);
		efree(url);
	}
}

static void mcrawler_settings_dtor(zend_resource *rsrc)
{
	mcrawler_settings *settings = (mcrawler_settings *)rsrc->ptr;
	if (settings) {
		efree(settings);
	}
}

static void mcrawler_url_url_dtor(zend_resource *rsrc)
{
	mcrawler_url_url *url = (mcrawler_url_url *)rsrc->ptr;
	if (url) {
		mcrawler_url_free_url(url);
		efree(url);
	}
}

PHP_MINIT_FUNCTION(minicrawler)
{
	le_mcrawler_url = zend_register_list_destructors_ex(mcrawler_url_dtor, NULL, MCRAWLER_URL_RES_NAME, module_number);
	le_mcrawler_settings = zend_register_list_destructors_ex(mcrawler_settings_dtor, NULL, MCRAWLER_SETTINGS_RES_NAME, module_number);
	le_mcrawler_url_url = zend_register_list_destructors_ex(mcrawler_url_url_dtor, NULL, MCRAWLER_URL_URL_RES_NAME, module_number);

	// MCURL_S_*
	REGISTER_LONG_CONSTANT("MCURL_S_JUSTBORN", MCURL_S_JUSTBORN, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("MCURL_S_PARSEDURL", MCURL_S_PARSEDURL, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("MCURL_S_INDNS", MCURL_S_INDNS, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("MCURL_S_GOTIP", MCURL_S_GOTIP, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("MCURL_S_CONNECT", MCURL_S_CONNECT, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("MCURL_S_HANDSHAKE", MCURL_S_HANDSHAKE, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("MCURL_S_GENREQUEST", MCURL_S_GENREQUEST, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("MCURL_S_SENDREQUEST", MCURL_S_SENDREQUEST, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("MCURL_S_RECVREPLY", MCURL_S_RECVREPLY, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("MCURL_S_DOWNLOADED", MCURL_S_DOWNLOADED, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("MCURL_S_ERROR", MCURL_S_ERROR, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("MCURL_S_DONE", MCURL_S_DONE, CONST_CS | CONST_PERSISTENT);

	// MCURL_OPT_*
	REGISTER_LONG_CONSTANT("MCURL_OPT_NONSSL", 1<<MCURL_OPT_NONSSL, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("MCURL_OPT_CONVERT_TO_TEXT", 1<<MCURL_OPT_CONVERT_TO_TEXT, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("MCURL_OPT_CONVERT_TO_UTF8", 1<<MCURL_OPT_CONVERT_TO_UTF8, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("MCURL_OPT_GZIP", 1<<MCURL_OPT_GZIP, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("MCURL_OPT_IPV6", 1<<MCURL_OPT_IPV6, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("MCURL_OPT_INSECURE", 1<<MCURL_OPT_INSECURE, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("MCURL_OPT_NOT_FOLLOW_REDIRECTS", 1<<MCURL_OPT_NOT_FOLLOW_REDIRECTS, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("MCURL_OPT_DISABLE_HTTP2", 1<<MCURL_OPT_DISABLE_HTTP2, CONST_CS | CONST_PERSISTENT);

	// MCURL_URL_PARSE_STATE_*
	REGISTER_LONG_CONSTANT("MCRAWLER_URL_PARSE_STATE_SCHEME_START", MCRAWLER_URL_PARSE_STATE_SCHEME_START, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("MCRAWLER_URL_PARSE_STATE_SCHEME", MCRAWLER_URL_PARSE_STATE_SCHEME, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("MCRAWLER_URL_PARSE_STATE_NO_SCHEME", MCRAWLER_URL_PARSE_STATE_NO_SCHEME, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("MCRAWLER_URL_PARSE_STATE_SPECIAL_RELATIVE_OR_AUTHORITY", MCRAWLER_URL_PARSE_STATE_SPECIAL_RELATIVE_OR_AUTHORITY, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("MCRAWLER_URL_PARSE_STATE_PATH_OR_AUTHORITY", MCRAWLER_URL_PARSE_STATE_PATH_OR_AUTHORITY, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("MCRAWLER_URL_PARSE_STATE_RELATIVE", MCRAWLER_URL_PARSE_STATE_RELATIVE, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("MCRAWLER_URL_PARSE_STATE_RELATIVE_SLASH", MCRAWLER_URL_PARSE_STATE_RELATIVE_SLASH, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("MCRAWLER_URL_PARSE_STATE_SPECIAL_AUTHORITY_SLASHES", MCRAWLER_URL_PARSE_STATE_SPECIAL_AUTHORITY_SLASHES, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("MCRAWLER_URL_PARSE_STATE_SPECIAL_AUTHORITY_IGNORE_SLASHES", MCRAWLER_URL_PARSE_STATE_SPECIAL_AUTHORITY_IGNORE_SLASHES, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("MCRAWLER_URL_PARSE_STATE_AUTHORITY", MCRAWLER_URL_PARSE_STATE_AUTHORITY, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("MCRAWLER_URL_PARSE_STATE_HOST", MCRAWLER_URL_PARSE_STATE_HOST, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("MCRAWLER_URL_PARSE_STATE_HOSTNAME", MCRAWLER_URL_PARSE_STATE_HOSTNAME, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("MCRAWLER_URL_PARSE_STATE_PORT", MCRAWLER_URL_PARSE_STATE_PORT, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("MCRAWLER_URL_PARSE_STATE_FILE", MCRAWLER_URL_PARSE_STATE_FILE, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("MCRAWLER_URL_PARSE_STATE_FILE_SLASH", MCRAWLER_URL_PARSE_STATE_FILE_SLASH, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("MCRAWLER_URL_PARSE_STATE_FILE_HOST", MCRAWLER_URL_PARSE_STATE_FILE_HOST, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("MCRAWLER_URL_PARSE_STATE_PATH_START", MCRAWLER_URL_PARSE_STATE_PATH_START, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("MCRAWLER_URL_PARSE_STATE_PATH", MCRAWLER_URL_PARSE_STATE_PATH, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("MCRAWLER_URL_PARSE_STATE_CANNOT_BE_A_BASE_URL_PATH", MCRAWLER_URL_PARSE_STATE_CANNOT_BE_A_BASE_URL_PATH, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("MCRAWLER_URL_PARSE_STATE_QUERY", MCRAWLER_URL_PARSE_STATE_QUERY, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("MCRAWLER_URL_PARSE_STATE_FRAGMENT", MCRAWLER_URL_PARSE_STATE_FRAGMENT, CONST_CS | CONST_PERSISTENT);

	zend_class_entry ce;
	zend_class_entry ce_url;
	INIT_CLASS_ENTRY(ce, "McrawlerException", NULL);
	INIT_CLASS_ENTRY(ce_url, "McrawlerUrlException", NULL);

	php_mcrawler_exception_ce = zend_register_internal_class_ex(&ce, zend_exception_get_default());
   php_mcrawler_url_exception_ce = zend_register_internal_class_ex(&ce_url, zend_exception_get_default());

	return SUCCESS;
}

static void php_minicrawler_register_url(mcrawler_url *url, zval *zurl) {
	php_mcrawler_ctx *ctx;

	ctx = (php_mcrawler_ctx *)emalloc(sizeof(php_mcrawler_ctx));
	url->userdata = ctx;

	ZVAL_RES(zurl, zend_register_resource(url, le_mcrawler_url));
	ctx->res = Z_RES_P(zurl);
}

PHP_FUNCTION(mcrawler_init_url)
{
	mcrawler_url *url;
	char *url_s, *method_s = NULL;
	int url_len, method_len = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS(), "s|s", &url_s, &url_len, &method_s, &method_len) == FAILURE) {
		RETURN_FALSE;
	}

	url = ecalloc(1, sizeof(mcrawler_url));

	mcrawler_init_url(url, url_s);
	if (method_s) {
		strncpy(url->method, method_s, sizeof(url->method) - 1);
	} else {
		strcpy(url->method, "GET");
	}

	php_minicrawler_register_url(url, return_value);
}

PHP_FUNCTION(mcrawler_close_url)
{
	zval *zurl;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_RESOURCE(zurl)
	ZEND_PARSE_PARAMETERS_END();

	zend_list_close(Z_RES_P(zurl));
	RETURN_TRUE;
}

PHP_FUNCTION(mcrawler_init_settings)
{
	mcrawler_settings *settings;
	long timeout = 5, delay = 100;

	if (zend_parse_parameters(ZEND_NUM_ARGS(), "|ll", &timeout, &delay) == FAILURE) {
		RETURN_FALSE;
	}

	settings = emalloc(sizeof(mcrawler_settings));
	mcrawler_init_settings(settings);
	settings->timeout = timeout;
	settings->delay = delay;

	RETURN_RES(zend_register_resource(settings, le_mcrawler_settings));
}

PHP_FUNCTION(mcrawler_close_settings)
{
	zval *zsetting;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_RESOURCE(zsetting)
	ZEND_PARSE_PARAMETERS_END();

	zend_list_close(Z_RES_P(zsetting));
	RETURN_TRUE;
}

PHP_FUNCTION(mcrawler_get_timeout)
{
	mcrawler_settings *settings;
	zval *zsettings;

	if (zend_parse_parameters(ZEND_NUM_ARGS(), "r", &zsettings) == FAILURE) {
		RETURN_FALSE;
	}

	if ((settings = (mcrawler_settings*)zend_fetch_resource(Z_RES_P(zsettings), MCRAWLER_SETTINGS_RES_NAME, le_mcrawler_settings)) == NULL) {
		RETURN_FALSE;
	}

	RETURN_LONG(settings->timeout);
}

PHP_FUNCTION(mcrawler_get_delay)
{
	mcrawler_settings *settings;
	zval *zsettings;

	if (zend_parse_parameters(ZEND_NUM_ARGS(), "r", &zsettings) == FAILURE) {
		RETURN_FALSE;
	}

	if ((settings = (mcrawler_settings*)zend_fetch_resource(Z_RES_P(zsettings), MCRAWLER_SETTINGS_RES_NAME, le_mcrawler_settings)) == NULL) {
		RETURN_FALSE;
	}

	RETURN_LONG(settings->delay);
}

PHP_FUNCTION(mcrawler_set_useragent)
{
	mcrawler_url  *url;
	zval          *zurl;
	zend_string   *useragent;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_RESOURCE(zurl)
		Z_PARAM_STR(useragent)
	ZEND_PARSE_PARAMETERS_END();

	if ((url = (mcrawler_url*)zend_fetch_resource(Z_RES_P(zurl), MCRAWLER_URL_RES_NAME, le_mcrawler_url)) == NULL) {
		RETURN_FALSE;
	}

	strncpy(url->customagent, ZSTR_VAL(useragent), ZSTR_LEN(useragent));
	RETURN_TRUE;
}

PHP_FUNCTION(mcrawler_set_headers)
{
	mcrawler_url  *url;
	zval          *zurl;
	zend_string   *headers;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_RESOURCE(zurl)
		Z_PARAM_STR(headers)
	ZEND_PARSE_PARAMETERS_END();

	if ((url = (mcrawler_url*)zend_fetch_resource(Z_RES_P(zurl), MCRAWLER_URL_RES_NAME, le_mcrawler_url)) == NULL) {
		RETURN_FALSE;
	}

	if (ZSTR_LEN(headers) > sizeof(url->customheader)-1) {
		php_error_docref(NULL, E_ERROR, "Custom HTTP headers are too long.");
		RETURN_FALSE;
	}
	strncpy(url->customheader, ZSTR_VAL(headers), ZSTR_LEN(headers));
	RETURN_TRUE;
}

PHP_FUNCTION(mcrawler_add_headers)
{
	mcrawler_url  *url;
	zval          *zurl;
	zend_string   *headers;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_RESOURCE(zurl)
		Z_PARAM_STR(headers)
	ZEND_PARSE_PARAMETERS_END();

	if ((url = (mcrawler_url*)zend_fetch_resource(Z_RES_P(zurl), MCRAWLER_URL_RES_NAME, le_mcrawler_url)) == NULL) {
		RETURN_FALSE;
	}

	size_t offset = strlen(url->customheader);
	if (offset + ZSTR_LEN(headers) > sizeof(url->customheader)-1) {
		php_error_docref(NULL, E_ERROR, "Custom HTTP headers are too long.");
		RETURN_FALSE;
	}
	strncpy(url->customheader + offset, ZSTR_VAL(headers), ZSTR_LEN(headers));
	RETURN_TRUE;
}

PHP_FUNCTION(mcrawler_set_credentials)
{
	mcrawler_url  *url;
	zval          *zurl;
	zend_string   *username, *password;

	ZEND_PARSE_PARAMETERS_START(3, 3)
		Z_PARAM_RESOURCE(zurl)
		Z_PARAM_STR(username)
		Z_PARAM_STR(password)
	ZEND_PARSE_PARAMETERS_END();

	if ((url = (mcrawler_url*)zend_fetch_resource(Z_RES_P(zurl), MCRAWLER_URL_RES_NAME, le_mcrawler_url)) == NULL) {
		RETURN_FALSE;
	}

	strncpy(url->username, ZSTR_VAL(username), sizeof(url->username) - 1);
	strncpy(url->password, ZSTR_VAL(password), sizeof(url->password) - 1);
	RETURN_TRUE;
}

PHP_FUNCTION(mcrawler_set_options)
{
	mcrawler_url  *url;
	zval          *zurl;
	long           options;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_RESOURCE(zurl)
		Z_PARAM_LONG(options)
	ZEND_PARSE_PARAMETERS_END();

	if ((url = (mcrawler_url*)zend_fetch_resource(Z_RES_P(zurl), MCRAWLER_URL_RES_NAME, le_mcrawler_url)) == NULL) {
		RETURN_FALSE;
	}

	url->options = options;
	RETURN_TRUE;
}

PHP_FUNCTION(mcrawler_set_option)
{
	mcrawler_url  *url;
	zval          *zurl;
	long           option;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_RESOURCE(zurl)
		Z_PARAM_LONG(option)
	ZEND_PARSE_PARAMETERS_END();

	if ((url = (mcrawler_url*)zend_fetch_resource(Z_RES_P(zurl), MCRAWLER_URL_RES_NAME, le_mcrawler_url)) == NULL) {
		RETURN_FALSE;
	}

	url->options |= option;
	RETURN_TRUE;
}

PHP_FUNCTION(mcrawler_set_postdata)
{
	mcrawler_url  *url;
	zval          *zurl;
	zend_string   *postdata;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_RESOURCE(zurl)
		Z_PARAM_STR(postdata)
	ZEND_PARSE_PARAMETERS_END();

	if ((url = (mcrawler_url*)zend_fetch_resource(Z_RES_P(zurl), MCRAWLER_URL_RES_NAME, le_mcrawler_url)) == NULL) {
		RETURN_FALSE;
	}

	if (url->post) free(url->post);
	url->post = malloc(ZSTR_LEN(postdata));
	url->postlen = ZSTR_LEN(postdata);
	memcpy(url->post, ZSTR_VAL(postdata), ZSTR_LEN(postdata));
	RETURN_TRUE;
}

static void scan_cookie(char **str, mcrawler_cookie *cookie) {
	char *q = strchrnul(*str, '\n'), *p = *str;
	cookie->name = malloc(q-p);
	cookie->value = malloc(q-p);
	cookie->domain = malloc(q-p);
	cookie->path = malloc(q-p);
	sscanf(p, "%s\t%d\t%s\t%d\t%ld\t%s\t%s", cookie->domain, &cookie->host_only, cookie->path, &cookie->secure, &cookie->expires, cookie->name, cookie->value);
	*str = (q[0] == '\n') ? q + 1 : q;
}

PHP_FUNCTION(mcrawler_set_cookies)
{
	mcrawler_url  *url;
	zval          *zurl;
	zend_string   *arg;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_RESOURCE(zurl)
		Z_PARAM_STR(arg)
	ZEND_PARSE_PARAMETERS_END();

	if ((url = (mcrawler_url*)zend_fetch_resource(Z_RES_P(zurl), MCRAWLER_URL_RES_NAME, le_mcrawler_url)) == NULL) {
		RETURN_FALSE;
	}

	char *p = ZSTR_VAL(arg);
	int i;

	for (i = 0; i < url->cookiecnt; i++) {
		mcrawler_free_cookie(&url->cookies[i]);
	}

	i = 0;
	while (p[0] != '\0' && i < sizeof(url->cookies)/sizeof(url->cookies[0])) {
		scan_cookie(&p, &url->cookies[i]);
		i++;
	}
	url->cookiecnt = i;

	RETURN_TRUE;
}

PHP_FUNCTION(mcrawler_add_cookies)
{
	mcrawler_url  *url;
	zval          *zurl;
	zend_string   *arg;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_RESOURCE(zurl)
		Z_PARAM_STR(arg)
	ZEND_PARSE_PARAMETERS_END();

	if ((url = (mcrawler_url*)zend_fetch_resource(Z_RES_P(zurl), MCRAWLER_URL_RES_NAME, le_mcrawler_url)) == NULL) {
		RETURN_FALSE;
	}

	char *p = ZSTR_VAL(arg);
	int i = url->cookiecnt;
	while (p[0] != '\0' && i < sizeof(url->cookies)/sizeof(url->cookies[0])) {
		scan_cookie(&p, &url->cookies[i]);
		i++;
	}
	url->cookiecnt = i;

	RETURN_TRUE;
}

struct fcall {
	zend_fcall_info info;
	zend_fcall_info_cache info_cache;
};

static void callback(mcrawler_url* url, void *arg) {
	struct fcall *fc = (struct fcall *)arg;
	php_mcrawler_ctx *ctx = (php_mcrawler_ctx *)url->userdata;

	zval args[1];
	zval retval;

	GC_ADDREF(ctx->res);
	ZVAL_RES(&args[0], ctx->res);

	fc->info.retval = &retval;
	fc->info.param_count = 1;
	fc->info.params = args;

	if (zend_call_function(&fc->info, &fc->info_cache) == SUCCESS) {
		zval_ptr_dtor(&retval);
	}
	zval_ptr_dtor(&args[0]);
}

PHP_FUNCTION(mcrawler_go)
{
	mcrawler_settings *settings;
	zval *zurls, *zsettings, *zurl;
	struct fcall fc;

	fc.info = empty_fcall_info;
	fc.info_cache = empty_fcall_info_cache;

	if (zend_parse_parameters(ZEND_NUM_ARGS(), "ar|f", &zurls, &zsettings, &fc.info, &fc.info_cache) == FAILURE) {
		RETURN_FALSE;
	}

	HashTable *arr_hash = Z_ARRVAL_P(zurls);
	HashPosition pointer;
	mcrawler_url *urls[zend_hash_num_elements(arr_hash) + 1];
	ulong ind;
	zend_string *key;
	int i = 0;

	for(zend_hash_internal_pointer_reset_ex(arr_hash, &pointer); (zurl = zend_hash_get_current_data_ex(arr_hash, &pointer)) != NULL; zend_hash_move_forward_ex(arr_hash, &pointer), i++) {
		if ((urls[i] = (mcrawler_url*)zend_fetch_resource(Z_RES_P(zurl), MCRAWLER_URL_RES_NAME, le_mcrawler_url)) == NULL) {
			RETURN_FALSE;
		}

		if (zend_hash_get_current_key_ex(arr_hash, &key, &ind, &pointer) == HASH_KEY_IS_LONG) {
			urls[i]->index = ind;
		} else {
			urls[i]->index = i;
		}
	}
	urls[i] = NULL;

	if ((settings = (mcrawler_settings*)zend_fetch_resource(Z_RES_P(zsettings), MCRAWLER_SETTINGS_RES_NAME, le_mcrawler_settings)) == NULL) {
		RETURN_FALSE;
	}

	mcrawler_go(urls, settings, callback, (void *)&fc);

	RETURN_TRUE;
}

PHP_FUNCTION(mcrawler_reset)
{
	mcrawler_url *url;
	zval *zurl;

	if (zend_parse_parameters(ZEND_NUM_ARGS(), "r", &zurl) == FAILURE) {
		RETURN_FALSE;
	}

	if ((url = (mcrawler_url*)zend_fetch_resource(Z_RES_P(zurl), MCRAWLER_URL_RES_NAME, le_mcrawler_url)) == NULL) {
		RETURN_FALSE;
	}

	mcrawler_reset_url(url);
}

PHP_FUNCTION(mcrawler_get_index)
{
	mcrawler_url *url;
	zval *zurl;

	if (zend_parse_parameters(ZEND_NUM_ARGS(), "r", &zurl) == FAILURE) {
		RETURN_FALSE;
	}

	if ((url = (mcrawler_url*)zend_fetch_resource(Z_RES_P(zurl), MCRAWLER_URL_RES_NAME, le_mcrawler_url)) == NULL) {
		RETURN_FALSE;
	}

	RETURN_LONG(url->index);
}

PHP_FUNCTION(mcrawler_get_state)
{
	mcrawler_url *url;
	zval *zurl;

	if (zend_parse_parameters(ZEND_NUM_ARGS(), "r", &zurl) == FAILURE) {
		RETURN_FALSE;
	}

	if ((url = (mcrawler_url*)zend_fetch_resource(Z_RES_P(zurl), MCRAWLER_URL_RES_NAME, le_mcrawler_url)) == NULL) {
		RETURN_FALSE;
	}

	RETURN_LONG(url->last_state);
}

PHP_FUNCTION(mcrawler_get_status)
{
	mcrawler_url *url;
	zval *zurl;

	if (zend_parse_parameters(ZEND_NUM_ARGS(), "r", &zurl) == FAILURE) {
		RETURN_FALSE;
	}

	if ((url = (mcrawler_url*)zend_fetch_resource(Z_RES_P(zurl), MCRAWLER_URL_RES_NAME, le_mcrawler_url)) == NULL) {
		RETURN_FALSE;
	}

	RETURN_LONG(url->status);
}

PHP_FUNCTION(mcrawler_get_url)
{
	mcrawler_url *url;
	zval *zurl;

	if (zend_parse_parameters(ZEND_NUM_ARGS(), "r", &zurl) == FAILURE) {
		RETURN_FALSE;
	}

	if ((url = (mcrawler_url*)zend_fetch_resource(Z_RES_P(zurl), MCRAWLER_URL_RES_NAME, le_mcrawler_url)) == NULL) {
		RETURN_FALSE;
	}

	RETURN_STRING(url->rawurl);
}

PHP_FUNCTION(mcrawler_get_method)
{
	mcrawler_url *url;
	zval *zurl;

	if (zend_parse_parameters(ZEND_NUM_ARGS(), "r", &zurl) == FAILURE) {
		RETURN_FALSE;
	}

	if ((url = (mcrawler_url*)zend_fetch_resource(Z_RES_P(zurl), MCRAWLER_URL_RES_NAME, le_mcrawler_url)) == NULL) {
		RETURN_FALSE;
	}

	RETURN_STRING(url->method);
}

PHP_FUNCTION(mcrawler_get_request)
{
	mcrawler_url *url;
	zval *zurl;

	if (zend_parse_parameters(ZEND_NUM_ARGS(), "r", &zurl) == FAILURE) {
		RETURN_FALSE;
	}

	if ((url = (mcrawler_url*)zend_fetch_resource(Z_RES_P(zurl), MCRAWLER_URL_RES_NAME, le_mcrawler_url)) == NULL) {
		RETURN_FALSE;
	}

	if (url->request) {
		RETURN_STRINGL((char *)url->request, url->request_len);
	} else {
		RETURN_NULL();
	}
}

PHP_FUNCTION(mcrawler_get_redirected_to)
{
	mcrawler_url *url;
	zval *zurl;

	if (zend_parse_parameters(ZEND_NUM_ARGS(), "r", &zurl) == FAILURE) {
		RETURN_FALSE;
	}

	if ((url = (mcrawler_url*)zend_fetch_resource(Z_RES_P(zurl), MCRAWLER_URL_RES_NAME, le_mcrawler_url)) == NULL) {
		RETURN_FALSE;
	}

	if (url->redirectedto) {
		RETURN_STRING(url->redirectedto);
	} else {
		RETURN_NULL();
	}
}

PHP_FUNCTION(mcrawler_get_redirect_info)
{
	mcrawler_url *url;
	zval *zurl;

	if (zend_parse_parameters(ZEND_NUM_ARGS(), "r", &zurl) == FAILURE) {
		RETURN_FALSE;
	}

	if ((url = (mcrawler_url*)zend_fetch_resource(Z_RES_P(zurl), MCRAWLER_URL_RES_NAME, le_mcrawler_url)) == NULL) {
		RETURN_FALSE;
	}

	int len = 0, total;
	mcrawler_redirect_info *rinfo = url->redirect_info;
	// at first count how many
	while (rinfo) {
		len++;
		rinfo = rinfo->next;
	}
	mcrawler_redirect_info *reversed[len];
	rinfo = url->redirect_info;
	total = len;
	// store reversed order to the array reversed
	while (rinfo) {
		reversed[--len] = rinfo;
		rinfo = rinfo->next;
	}

	zval info, timing;
	array_init(return_value);

	while (len < total) {
		array_init(&info);

		timing_to_zval(&reversed[len]->timing, MCURL_S_DOWNLOADED, &timing);

		add_assoc_string(&info, "url", reversed[len]->url);
		add_assoc_long(&info, "status", reversed[len]->status);
		add_assoc_zval(&info, "timing", &timing);
		add_next_index_zval(return_value, &info);
		len++;
	}
}

PHP_FUNCTION(mcrawler_get_header)
{
	mcrawler_url *url;
	zval *zurl;

	if (zend_parse_parameters(ZEND_NUM_ARGS(), "r", &zurl) == FAILURE) {
		RETURN_FALSE;
	}

	if ((url = (mcrawler_url*)zend_fetch_resource(Z_RES_P(zurl), MCRAWLER_URL_RES_NAME, le_mcrawler_url)) == NULL) {
		RETURN_FALSE;
	}

	unsigned char *header;
	size_t len;

	mcrawler_url_header(url, &header, &len);

	RETURN_STRINGL((char *)header, len);
}

PHP_FUNCTION(mcrawler_get_body)
{
	mcrawler_url *url;
	zval *zurl;

	if (zend_parse_parameters(ZEND_NUM_ARGS(), "r", &zurl) == FAILURE) {
		RETURN_FALSE;
	}

	if ((url = (mcrawler_url*)zend_fetch_resource(Z_RES_P(zurl), MCRAWLER_URL_RES_NAME, le_mcrawler_url)) == NULL) {
		RETURN_FALSE;
	}

	unsigned char *body;
	size_t len;

	mcrawler_url_body(url, &body, &len);

	RETURN_STRINGL((char *)body, len);
}

PHP_FUNCTION(mcrawler_get_response_size)
{
	mcrawler_url *url;
	zval *zurl;

	if (zend_parse_parameters(ZEND_NUM_ARGS(), "r", &zurl) == FAILURE) {
		RETURN_FALSE;
	}

	if ((url = (mcrawler_url*)zend_fetch_resource(Z_RES_P(zurl), MCRAWLER_URL_RES_NAME, le_mcrawler_url)) == NULL) {
		RETURN_FALSE;
	}

	unsigned char *header, *body;
	size_t header_len, body_len;

	mcrawler_url_header(url, &header, &header_len);
	mcrawler_url_body(url, &body, &body_len);

	RETURN_LONG((long)header_len + body_len);
}

PHP_FUNCTION(mcrawler_get_options)
{
	mcrawler_url *url;
	zval *zurl;

	if (zend_parse_parameters(ZEND_NUM_ARGS(), "r", &zurl) == FAILURE) {
		RETURN_FALSE;
	}

	if ((url = (mcrawler_url*)zend_fetch_resource(Z_RES_P(zurl), MCRAWLER_URL_RES_NAME, le_mcrawler_url)) == NULL) {
		RETURN_FALSE;
	}

	RETURN_LONG(url->options);
}

PHP_FUNCTION(mcrawler_get_timing)
{
	mcrawler_url *url;
	zval *zurl;

	if (zend_parse_parameters(ZEND_NUM_ARGS(), "r", &zurl) == FAILURE) {
		RETURN_FALSE;
	}

	if ((url = (mcrawler_url*)zend_fetch_resource(Z_RES_P(zurl), MCRAWLER_URL_RES_NAME, le_mcrawler_url)) == NULL) {
		RETURN_FALSE;
	}

	timing_to_zval(&url->timing, url->last_state, return_value);
}

PHP_FUNCTION(mcrawler_get_cookies)
{
	mcrawler_url *url;
	zval *zurl;

	if (zend_parse_parameters(ZEND_NUM_ARGS(), "r", &zurl) == FAILURE) {
		RETURN_FALSE;
	}

	if ((url = (mcrawler_url*)zend_fetch_resource(Z_RES_P(zurl), MCRAWLER_URL_RES_NAME, le_mcrawler_url)) == NULL) {
		RETURN_FALSE;
	}

	const char linefmt[] = "%s\t%d\t%s\t%d\t%ld\t%s\t%s\n";
	size_t cookies_size = 0;
	for (int i = 0; i < url->cookiecnt; i++) {
		cookies_size += 
			strlen(linefmt) +
			strlen(url->cookies[i].domain) +
			10 + 10 + 10 + // 3krát integer
			strlen(url->cookies[i].path) +
			strlen(url->cookies[i].name) +
			strlen(url->cookies[i].value);
	}

	char buff[cookies_size + 1];
	int len = 0, n;
	if (url->cookiecnt) {
		// netscape cookies.txt format
		// @see http://www.cookiecentral.com/faq/#3.5
		for (int i = 0; i < url->cookiecnt; i++) {
			n = sprintf(buff+len, linefmt, url->cookies[i].domain, url->cookies[i].host_only, url->cookies[i].path, url->cookies[i].secure, url->cookies[i].expires, url->cookies[i].name, url->cookies[i].value);
			if (n > 0) len += n;
		}
	}
	buff[len] = 0;

	RETURN_STRING(buff);
}

PHP_FUNCTION(mcrawler_get_content_type)
{
	mcrawler_url *url;
	zval *zurl;

	if (zend_parse_parameters(ZEND_NUM_ARGS(), "r", &zurl) == FAILURE) {
		RETURN_FALSE;
	}

	if ((url = (mcrawler_url*)zend_fetch_resource(Z_RES_P(zurl), MCRAWLER_URL_RES_NAME, le_mcrawler_url)) == NULL) {
		RETURN_FALSE;
	}

	if (url->contenttype) {
		RETURN_STRING(url->contenttype);
	} else {
		RETURN_NULL();
	}
}

PHP_FUNCTION(mcrawler_get_charset)
{
	mcrawler_url *url;
	zval *zurl;

	if (zend_parse_parameters(ZEND_NUM_ARGS(), "r", &zurl) == FAILURE) {
		RETURN_FALSE;
	}

	if ((url = (mcrawler_url*)zend_fetch_resource(Z_RES_P(zurl), MCRAWLER_URL_RES_NAME, le_mcrawler_url)) == NULL) {
		RETURN_FALSE;
	}

	if (url->contenttype) {
		RETURN_STRING(url->charset);
	} else {
		RETURN_NULL();
	}
}

PHP_FUNCTION(mcrawler_get_www_authenticate)
{
	mcrawler_url *url;
	zval *zurl;

	if (zend_parse_parameters(ZEND_NUM_ARGS(), "r", &zurl) == FAILURE) {
		RETURN_FALSE;
	}

	if ((url = (mcrawler_url*)zend_fetch_resource(Z_RES_P(zurl), MCRAWLER_URL_RES_NAME, le_mcrawler_url)) == NULL) {
		RETURN_FALSE;
	}

	if (url->wwwauthenticate) {
		RETURN_STRING(url->wwwauthenticate);
	} else {
		RETURN_NULL();
	}
}

PHP_FUNCTION(mcrawler_get_error_msg)
{
	mcrawler_url *url;
	zval *zurl;

	if (zend_parse_parameters(ZEND_NUM_ARGS(), "r", &zurl) == FAILURE) {
		RETURN_FALSE;
	}

	if ((url = (mcrawler_url*)zend_fetch_resource(Z_RES_P(zurl), MCRAWLER_URL_RES_NAME, le_mcrawler_url)) == NULL) {
		RETURN_FALSE;
	}

	RETURN_STRING(url->error_msg);
}

PHP_FUNCTION(mcrawler_serialize)
{
	mcrawler_settings *settings;
	zval *zurls, *zsettings, *zurl;

	if (zend_parse_parameters(ZEND_NUM_ARGS(), "ar", &zurls, &zsettings) == FAILURE) {
		RETURN_FALSE;
	}

	HashTable *arr_hash = Z_ARRVAL_P(zurls);
	HashPosition pointer;
	mcrawler_url *urls[zend_hash_num_elements(arr_hash) + 1];
	ulong ind;
	zend_string *key;
	int i = 0;

	for(zend_hash_internal_pointer_reset_ex(arr_hash, &pointer); (zurl = zend_hash_get_current_data_ex(arr_hash, &pointer)) != NULL; zend_hash_move_forward_ex(arr_hash, &pointer), i++) {
		if ((urls[i] = (mcrawler_url*)zend_fetch_resource(Z_RES_P(zurl), MCRAWLER_URL_RES_NAME, le_mcrawler_url)) == NULL) {
			RETURN_FALSE;
		}

		if (zend_hash_get_current_key_ex(arr_hash, &key, &ind, &pointer) == HASH_KEY_IS_LONG) {
			urls[i]->index = ind;
		} else {
			urls[i]->index = i;
		}
	}
	urls[i] = NULL;

	if ((settings = (mcrawler_settings*)zend_fetch_resource(Z_RES_P(zsettings), MCRAWLER_SETTINGS_RES_NAME, le_mcrawler_settings)) == NULL) {
		RETURN_FALSE;
	}

	void *buf;
	int buf_sz;

	mcrawler_urls_serialize(urls, settings, &buf, &buf_sz);

	RETVAL_STRINGL(buf, buf_sz);
	free(buf);
}

static void *emalloc_func(size_t size) {
	return emalloc(size);
}

PHP_FUNCTION(mcrawler_unserialize)
{
	mcrawler_url **urls;
	mcrawler_settings *settings;
	char *buf;
	int buf_sz;

	if (zend_parse_parameters(ZEND_NUM_ARGS(), "s", &buf, &buf_sz) == FAILURE) {
		RETURN_FALSE;
	}

	mcrawler_urls_unserialize(&urls, &settings, buf, buf_sz, emalloc_func);

	array_init(return_value);
	zval  zurls, zurl;
	zval  zsettings;

	array_init(&zurls);

	for (int i = 0; urls[i]; i++) {
		php_minicrawler_register_url(urls[i], &zurl);
		add_index_zval(&zurls, urls[i]->index, &zurl);
	}

	add_next_index_zval(return_value, &zurls);

	ZVAL_RES(&zsettings, zend_register_resource(settings, le_mcrawler_settings));
	add_next_index_zval(return_value, &zsettings);
}

PHP_FUNCTION(mcrawler_version)
{
	RETURN_STRING(mcrawler_version());
}

void timing_to_zval(mcrawler_timing *timing, int state, zval *ret)
{
	array_init(ret);
	if (timing->dnsstart) {
		zval timingArray;

		array_init(&timingArray);
		add_assoc_string(&timingArray, "metric", "DNS Lookup");
		add_assoc_long(&timingArray, "value", (timing->dnsend ? timing->dnsend : timing->done) - timing->dnsstart);
		add_next_index_zval(ret, &timingArray);
	}

	if (timing->connectionstart) {
		zval timingArray;

		array_init(&timingArray);
		add_assoc_string(&timingArray, "metric", "Initial connection");
		add_assoc_long(&timingArray, "value", (timing->requeststart ? timing->requeststart : timing->done) - timing->connectionstart);
		add_next_index_zval(ret, &timingArray);
	}

	if (timing->sslstart) {
		zval timingArray;

		array_init(&timingArray);
		add_assoc_string(&timingArray, "metric", "SSL");
		add_assoc_long(&timingArray, "value", (timing->sslend ? timing->sslend : timing->done) - timing->sslstart);
		add_next_index_zval(ret, &timingArray);
	}

	if (timing->requeststart) {
		zval timingArray;

		array_init(&timingArray);
		add_assoc_string(&timingArray, "metric", "Request");
		add_assoc_long(&timingArray, "value", (timing->requestend ? timing->requestend : timing->done) - timing->requeststart);
		add_next_index_zval(ret, &timingArray);
	}

	if (timing->requestend) {
		zval timingArray;

		array_init(&timingArray);
		add_assoc_string(&timingArray, "metric", "Waiting");
		add_assoc_long(&timingArray, "value", (timing->firstbyte ? timing->firstbyte : timing->done) - timing->requestend);
		add_next_index_zval(ret, &timingArray);
	}

	if (timing->firstbyte) {
		zval timingArray;

		array_init(&timingArray);
		add_assoc_string(&timingArray, "metric", "Content download");
		add_assoc_long(&timingArray, "value", (timing->lastread && state > MCURL_S_RECVREPLY ? timing->lastread : timing->done) - timing->firstbyte);
		add_next_index_zval(ret, &timingArray);
	}

	if (timing->connectionstart) {
		zval timingArray;

		array_init(&timingArray);
		add_assoc_string(&timingArray, "metric", "Total");
		add_assoc_long(&timingArray, "value", (timing->lastread && state > MCURL_S_RECVREPLY ? timing->lastread : timing->done) - timing->connectionstart);
		add_next_index_zval(ret, &timingArray);
	}
}

PHP_FUNCTION(mcrawler_parse_url)
{
	zval             *zbase_url = NULL;
	zend_string      *input;
	mcrawler_url_url  base_url, *url, *p_base_url;

	ZEND_PARSE_PARAMETERS_START(1, 2)
		Z_PARAM_STR(input)
		Z_PARAM_OPTIONAL
		Z_PARAM_ZVAL(zbase_url)
	ZEND_PARSE_PARAMETERS_END();

	if (zbase_url) {
		switch (Z_TYPE_P(zbase_url)) {
			case IS_NULL:
				p_base_url = NULL;
				break;
			case IS_STRING:
				if (mcrawler_url_parse(&base_url, Z_STRVAL_P(zbase_url), NULL) == MCRAWLER_URL_FAILURE) {
					zend_throw_exception_ex(php_mcrawler_url_exception_ce, 0, "Invalid base URL");
					RETURN_FALSE;
				}
				p_base_url = &base_url;
				break;
			case IS_RESOURCE:
				if ((p_base_url = (mcrawler_url_url*)zend_fetch_resource(Z_RES_P(zbase_url), MCRAWLER_URL_URL_RES_NAME, le_mcrawler_url_url)) == NULL) {
					RETURN_FALSE;
				}
				break;
			default:
				php_error_docref(NULL, E_ERROR, "Invalid type for base URL, only string or resource allowed.");
				RETURN_FALSE;
		}
	} else {
		p_base_url = NULL;
	}

	url = emalloc(sizeof(mcrawler_url_url));
	mcrawler_url_parse_state state;

	if (mcrawler_url_parse2(url, ZSTR_VAL(input), p_base_url, &state) == MCRAWLER_URL_FAILURE) {
		efree(url);
		zend_throw_exception_ex(php_mcrawler_url_exception_ce, state, "Invalid URL");
		RETURN_FALSE;
	}

	char *tmp;

	array_init(return_value);

	zval zurl;

	ZVAL_RES(&zurl, zend_register_resource(url, le_mcrawler_url_url));
	add_assoc_zval(return_value, "resource", &zurl);

	add_assoc_str(return_value, "input", input);
	tmp = mcrawler_url_get_href(url);
	add_assoc_string(return_value, "href", tmp);
	free(tmp);
	tmp = mcrawler_url_get_protocol(url);
	add_assoc_string(return_value, "protocol", tmp);
	free(tmp);
	tmp = mcrawler_url_get_username(url);
	add_assoc_string(return_value, "username", tmp);
	free(tmp);
	tmp = mcrawler_url_get_password(url);
	add_assoc_string(return_value, "password", tmp);
	free(tmp);
	char hostname[256];
	mcrawler_url_get_hostname(url, hostname);
	add_assoc_string(return_value, "hostname", hostname);
	char host[256 + 6];
	mcrawler_url_get_host(url, host);
	add_assoc_string(return_value, "host", host);
	tmp = mcrawler_url_get_port(url);
	add_assoc_string(return_value, "port", tmp);
	free(tmp);
	tmp = mcrawler_url_get_pathname(url);
	add_assoc_string(return_value, "pathname", tmp);
	free(tmp);
	tmp = mcrawler_url_get_search(url);
	add_assoc_string(return_value, "search", tmp);
	free(tmp);
	tmp = mcrawler_url_get_hash(url);
	add_assoc_string(return_value, "hash", tmp);
	free(tmp);
}
