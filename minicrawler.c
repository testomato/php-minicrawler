#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include "php.h"
#include "php_minicrawler.h"
#include "zend_exceptions.h"

int le_mcrawler_url;
int le_mcrawler_settings;
int le_mcrawler_url_url;

static zend_function_entry minicrawler_functions[] = {
    PHP_FE(mcrawler_init_url, NULL)
    PHP_FE(mcrawler_init_settings, NULL)
    PHP_FE(mcrawler_close_url, NULL)
    PHP_FE(mcrawler_close_settings, NULL)
    PHP_FE(mcrawler_get_timeout, NULL)
    PHP_FE(mcrawler_get_delay, NULL)
    PHP_FE(mcrawler_set_useragent, NULL)
    PHP_FE(mcrawler_set_headers, NULL)
    PHP_FE(mcrawler_add_headers, NULL)
    PHP_FE(mcrawler_set_credentials, NULL)
    PHP_FE(mcrawler_set_postdata, NULL)
    PHP_FE(mcrawler_set_options, NULL)
    PHP_FE(mcrawler_set_option, NULL)
    PHP_FE(mcrawler_set_cookies, NULL)
    PHP_FE(mcrawler_add_cookies, NULL)
    PHP_FE(mcrawler_go, NULL)
    PHP_FE(mcrawler_reset, NULL)
    PHP_FE(mcrawler_get_index, NULL)
    PHP_FE(mcrawler_get_state, NULL)
    PHP_FE(mcrawler_get_status, NULL)
    PHP_FE(mcrawler_get_url, NULL)
    PHP_FE(mcrawler_get_method, NULL)
    PHP_FE(mcrawler_get_request, NULL)
    PHP_FE(mcrawler_get_redirected_to, NULL)
    PHP_FE(mcrawler_get_redirect_info, NULL)
    PHP_FE(mcrawler_get_header, NULL)
    PHP_FE(mcrawler_get_body, NULL)
    PHP_FE(mcrawler_get_response_size, NULL)
    PHP_FE(mcrawler_get_options, NULL)
    PHP_FE(mcrawler_get_timing, NULL)
    PHP_FE(mcrawler_get_cookies, NULL)
    PHP_FE(mcrawler_get_content_type, NULL)
    PHP_FE(mcrawler_get_charset, NULL)
    PHP_FE(mcrawler_get_www_authenticate, NULL)
    PHP_FE(mcrawler_get_error_msg, NULL)
    PHP_FE(mcrawler_serialize, NULL)
    PHP_FE(mcrawler_unserialize, NULL)
    PHP_FE(mcrawler_version, NULL)
    PHP_FE(mcrawler_parse_url, NULL)
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

static void mcrawler_url_dtor(zend_rsrc_list_entry *rsrc TSRMLS_DC)
{
	mcrawler_url *url = (mcrawler_url *)rsrc->ptr;
	if (url) {
		efree(url->userdata);
		mcrawler_free_url(url);
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

static void mcrawler_url_url_dtor(zend_rsrc_list_entry *rsrc TSRMLS_DC)
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

	php_mcrawler_exception_ce = zend_register_internal_class_ex(&ce, zend_exception_get_default(TSRMLS_CC), NULL TSRMLS_CC);
	php_mcrawler_url_exception_ce = zend_register_internal_class_ex(&ce_url, zend_exception_get_default(TSRMLS_CC), NULL TSRMLS_CC);

	return SUCCESS;
}

static void php_minicrawler_register_url(mcrawler_url *url, zval *zurl TSRMLS_DC) {
	php_mcrawler_ctx *ctx;

	ctx = (php_mcrawler_ctx *)emalloc(sizeof(php_mcrawler_ctx));
	TSRMLS_SET_CTX(ctx->thread_ctx);
	url->userdata = ctx;

	ZEND_REGISTER_RESOURCE(zurl, url, le_mcrawler_url);
	ctx->id = Z_LVAL_P(zurl);
}

PHP_FUNCTION(mcrawler_init_url)
{
    mcrawler_url *url;
	char *url_s, *method_s = NULL;
	int url_len, method_len = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s|s", &url_s, &url_len, &method_s, &method_len) == FAILURE) {
		RETURN_FALSE;
	}

	url = emalloc(sizeof(mcrawler_url));
	memset(url, 0, sizeof(mcrawler_url));

	mcrawler_init_url(url, url_s);
	if (method_s) {
		strncpy(url->method, method_s, sizeof(url->method) - 1);
	} else {
		strcpy(url->method, "GET");
	}

	php_minicrawler_register_url(url, return_value TSRMLS_CC);
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

PHP_FUNCTION(mcrawler_get_timeout)
{
	mcrawler_settings *settings;
	zval *zsettings;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "r", &zsettings) == FAILURE) {
		RETURN_FALSE;
	}
	ZEND_FETCH_RESOURCE(settings, mcrawler_settings*, &zsettings, -1, MCRAWLER_SETTINGS_RES_NAME, le_mcrawler_settings);

	RETURN_LONG(settings->timeout);
}

PHP_FUNCTION(mcrawler_get_delay)
{
	mcrawler_settings *settings;
	zval *zsettings;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "r", &zsettings) == FAILURE) {
		RETURN_FALSE;
	}
	ZEND_FETCH_RESOURCE(settings, mcrawler_settings*, &zsettings, -1, MCRAWLER_SETTINGS_RES_NAME, le_mcrawler_settings);

	RETURN_LONG(settings->delay);
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

	if (headers_len > sizeof(url->customheader)-1) {
		php_error_docref(NULL TSRMLS_CC, E_ERROR, "Custom HTTP headers are too long.");
		RETURN_FALSE;
	}
	strcpy(url->customheader, headers);
	RETURN_TRUE;
}

PHP_FUNCTION(mcrawler_add_headers)
{
	mcrawler_url *url;
	zval *zurl;
	char *headers;
	int headers_len;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "rs", &zurl, &headers, &headers_len) == FAILURE) {
		RETURN_FALSE;
	}
	ZEND_FETCH_RESOURCE(url, mcrawler_url*, &zurl, -1, MCRAWLER_URL_RES_NAME, le_mcrawler_url);

	size_t offset = strlen(url->customheader);
	if (offset + headers_len > sizeof(url->customheader)-1) {
		php_error_docref(NULL TSRMLS_CC, E_ERROR, "Custom HTTP headers are too long.");
		RETURN_FALSE;
	}
	strcpy(url->customheader + offset, headers);
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

PHP_FUNCTION(mcrawler_set_options)
{
	mcrawler_url *url;
	zval *zurl;
	long options;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "rl", &zurl, &options) == FAILURE) {
		RETURN_FALSE;
	}
	ZEND_FETCH_RESOURCE(url, mcrawler_url*, &zurl, -1, MCRAWLER_URL_RES_NAME, le_mcrawler_url);

	url->options = options;
	RETURN_TRUE;
}

PHP_FUNCTION(mcrawler_set_option)
{
	mcrawler_url *url;
	zval *zurl;
	long option;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "rl", &zurl, &option) == FAILURE) {
		RETURN_FALSE;
	}
	ZEND_FETCH_RESOURCE(url, mcrawler_url*, &zurl, -1, MCRAWLER_URL_RES_NAME, le_mcrawler_url);

	url->options |= option;
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

	if (url->post) free(url->post);
	url->post = malloc(postdata_len);
	url->postlen = postdata_len;
	memcpy(url->post, postdata, postdata_len);
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
	mcrawler_url *url;
	zval *zurl;
	char *arg;
	int arg_len;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "rs", &zurl, &arg, &arg_len) == FAILURE) {
		RETURN_FALSE;
	}
	ZEND_FETCH_RESOURCE(url, mcrawler_url*, &zurl, -1, MCRAWLER_URL_RES_NAME, le_mcrawler_url);

	char *p = arg;
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
	mcrawler_url *url;
	zval *zurl;
	char *arg;
	int arg_len;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "rs", &zurl, &arg, &arg_len) == FAILURE) {
		RETURN_FALSE;
	}
	ZEND_FETCH_RESOURCE(url, mcrawler_url*, &zurl, -1, MCRAWLER_URL_RES_NAME, le_mcrawler_url);

	char *p = arg;
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
	TSRMLS_FETCH_FROM_CTX(ctx->thread_ctx);

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
	ulong ind;
	char *key;
	int i = 0;
	uint keylen;

	for(zend_hash_internal_pointer_reset_ex(arr_hash, &pointer); zend_hash_get_current_data_ex(arr_hash, (void**) &zurl, &pointer) == SUCCESS; zend_hash_move_forward_ex(arr_hash, &pointer), i++) {
		ZEND_FETCH_RESOURCE(urls[i], mcrawler_url*, zurl, -1, MCRAWLER_URL_RES_NAME, le_mcrawler_url);

		if (zend_hash_get_current_key_ex(arr_hash, &key, &keylen, &ind, 0, &pointer) == HASH_KEY_IS_LONG) {
			urls[i]->index = ind;
		} else {
			urls[i]->index = i;
		}
	}
	urls[i] = NULL;

	ZEND_FETCH_RESOURCE(settings, mcrawler_settings*, &zsettings, -1, MCRAWLER_SETTINGS_RES_NAME, le_mcrawler_settings);

	mcrawler_go(urls, settings, callback, (void *)&fc);

	RETURN_TRUE;
}

PHP_FUNCTION(mcrawler_reset)
{
	mcrawler_url *url;
	zval *zurl;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "r", &zurl) == FAILURE) {
		RETURN_FALSE;
	}
	ZEND_FETCH_RESOURCE(url, mcrawler_url*, &zurl, -1, MCRAWLER_URL_RES_NAME, le_mcrawler_url);

	mcrawler_reset_url(url);
}

PHP_FUNCTION(mcrawler_get_index)
{
	mcrawler_url *url;
	zval *zurl;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "r", &zurl) == FAILURE) {
		RETURN_FALSE;
	}
	ZEND_FETCH_RESOURCE(url, mcrawler_url*, &zurl, -1, MCRAWLER_URL_RES_NAME, le_mcrawler_url);

	RETURN_LONG(url->index);
}

PHP_FUNCTION(mcrawler_get_state)
{
	mcrawler_url *url;
	zval *zurl;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "r", &zurl) == FAILURE) {
		RETURN_FALSE;
	}
	ZEND_FETCH_RESOURCE(url, mcrawler_url*, &zurl, -1, MCRAWLER_URL_RES_NAME, le_mcrawler_url);

	RETURN_LONG(url->last_state);
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

PHP_FUNCTION(mcrawler_get_method)
{
	mcrawler_url *url;
	zval *zurl;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "r", &zurl) == FAILURE) {
		RETURN_FALSE;
	}
	ZEND_FETCH_RESOURCE(url, mcrawler_url*, &zurl, -1, MCRAWLER_URL_RES_NAME, le_mcrawler_url);

	RETURN_STRING(url->method, 1);
}

PHP_FUNCTION(mcrawler_get_request)
{
	mcrawler_url *url;
	zval *zurl;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "r", &zurl) == FAILURE) {
		RETURN_FALSE;
	}
	ZEND_FETCH_RESOURCE(url, mcrawler_url*, &zurl, -1, MCRAWLER_URL_RES_NAME, le_mcrawler_url);

	if (url->request) {
		RETURN_STRINGL((char *)url->request, url->request_len, 1);
	} else {
		RETURN_NULL();
	}
}

PHP_FUNCTION(mcrawler_get_redirected_to)
{
	mcrawler_url *url;
	zval *zurl;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "r", &zurl) == FAILURE) {
		RETURN_FALSE;
	}
	ZEND_FETCH_RESOURCE(url, mcrawler_url*, &zurl, -1, MCRAWLER_URL_RES_NAME, le_mcrawler_url);

	if (url->redirectedto) {
		RETURN_STRING(url->redirectedto, 1);
	} else {
		RETURN_NULL();
	}
}

PHP_FUNCTION(mcrawler_get_redirect_info)
{
	mcrawler_url *url;
	zval *zurl;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "r", &zurl) == FAILURE) {
		RETURN_FALSE;
	}
	ZEND_FETCH_RESOURCE(url, mcrawler_url*, &zurl, -1, MCRAWLER_URL_RES_NAME, le_mcrawler_url);

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

	zval *info, *timing;
	array_init(return_value);

	while (len < total) {
		ALLOC_INIT_ZVAL(info);
		array_init(info);

		ALLOC_INIT_ZVAL(timing);
		timing_to_zval(&reversed[len]->timing, MCURL_S_DOWNLOADED, timing);

		add_assoc_string(info, "url", reversed[len]->url, 1);
		add_assoc_long(info, "status", reversed[len]->status);
		add_assoc_zval(info, "timing", timing);
		add_next_index_zval(return_value, info);
		len++;
	}
}

PHP_FUNCTION(mcrawler_get_header)
{
	mcrawler_url *url;
	zval *zurl;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "r", &zurl) == FAILURE) {
		RETURN_FALSE;
	}
	ZEND_FETCH_RESOURCE(url, mcrawler_url*, &zurl, -1, MCRAWLER_URL_RES_NAME, le_mcrawler_url);

	unsigned char *header;
	size_t len;

	mcrawler_url_header(url, &header, &len);

	RETURN_STRINGL((char *)header, len, 1);
}

PHP_FUNCTION(mcrawler_get_body)
{
	mcrawler_url *url;
	zval *zurl;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "r", &zurl) == FAILURE) {
		RETURN_FALSE;
	}
	ZEND_FETCH_RESOURCE(url, mcrawler_url*, &zurl, -1, MCRAWLER_URL_RES_NAME, le_mcrawler_url);

	unsigned char *body;
	size_t len;

	mcrawler_url_body(url, &body, &len);

	RETURN_STRINGL((char *)body, len, 1);
}

PHP_FUNCTION(mcrawler_get_response_size)
{
	mcrawler_url *url;
	zval *zurl;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "r", &zurl) == FAILURE) {
		RETURN_FALSE;
	}
	ZEND_FETCH_RESOURCE(url, mcrawler_url*, &zurl, -1, MCRAWLER_URL_RES_NAME, le_mcrawler_url);

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

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "r", &zurl) == FAILURE) {
		RETURN_FALSE;
	}
	ZEND_FETCH_RESOURCE(url, mcrawler_url*, &zurl, -1, MCRAWLER_URL_RES_NAME, le_mcrawler_url);

	RETURN_LONG(url->options);
}

PHP_FUNCTION(mcrawler_get_timing)
{
	mcrawler_url *url;
	zval *zurl;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "r", &zurl) == FAILURE) {
		RETURN_FALSE;
	}
	ZEND_FETCH_RESOURCE(url, mcrawler_url*, &zurl, -1, MCRAWLER_URL_RES_NAME, le_mcrawler_url);

	timing_to_zval(&url->timing, url->last_state, return_value);
}

PHP_FUNCTION(mcrawler_get_cookies)
{
	mcrawler_url *url;
	zval *zurl;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "r", &zurl) == FAILURE) {
		RETURN_FALSE;
	}
	ZEND_FETCH_RESOURCE(url, mcrawler_url*, &zurl, -1, MCRAWLER_URL_RES_NAME, le_mcrawler_url);

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

	RETURN_STRING(buff, 1);
}

PHP_FUNCTION(mcrawler_get_content_type)
{
	mcrawler_url *url;
	zval *zurl;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "r", &zurl) == FAILURE) {
		RETURN_FALSE;
	}
	ZEND_FETCH_RESOURCE(url, mcrawler_url*, &zurl, -1, MCRAWLER_URL_RES_NAME, le_mcrawler_url);

	if (url->contenttype) {
		RETURN_STRING(url->contenttype, 1);
	} else {
		RETURN_NULL();
	}
}

PHP_FUNCTION(mcrawler_get_charset)
{
	mcrawler_url *url;
	zval *zurl;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "r", &zurl) == FAILURE) {
		RETURN_FALSE;
	}
	ZEND_FETCH_RESOURCE(url, mcrawler_url*, &zurl, -1, MCRAWLER_URL_RES_NAME, le_mcrawler_url);

	if (url->contenttype) {
		RETURN_STRING(url->charset, 1);
	} else {
		RETURN_NULL();
	}
}

PHP_FUNCTION(mcrawler_get_www_authenticate)
{
	mcrawler_url *url;
	zval *zurl;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "r", &zurl) == FAILURE) {
		RETURN_FALSE;
	}
	ZEND_FETCH_RESOURCE(url, mcrawler_url*, &zurl, -1, MCRAWLER_URL_RES_NAME, le_mcrawler_url);

	if (url->wwwauthenticate) {
		RETURN_STRING(url->wwwauthenticate, 1);
	} else {
		RETURN_NULL();
	}
}

PHP_FUNCTION(mcrawler_get_error_msg)
{
	mcrawler_url *url;
	zval *zurl;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "r", &zurl) == FAILURE) {
		RETURN_FALSE;
	}
	ZEND_FETCH_RESOURCE(url, mcrawler_url*, &zurl, -1, MCRAWLER_URL_RES_NAME, le_mcrawler_url);

	RETURN_STRING(url->error_msg, 1);
}

PHP_FUNCTION(mcrawler_serialize)
{
	mcrawler_settings *settings;
	zval *zurls, *zsettings, **zurl;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "ar", &zurls, &zsettings) == FAILURE) {
		RETURN_FALSE;
	}

	HashTable *arr_hash = Z_ARRVAL_P(zurls);
	HashPosition pointer;
	mcrawler_url *urls[zend_hash_num_elements(arr_hash) + 1];
	ulong ind;
	char *key;
	uint keylen;
	int i = 0;

	for(zend_hash_internal_pointer_reset_ex(arr_hash, &pointer); zend_hash_get_current_data_ex(arr_hash, (void**) &zurl, &pointer) == SUCCESS; zend_hash_move_forward_ex(arr_hash, &pointer), i++) {
		ZEND_FETCH_RESOURCE(urls[i], mcrawler_url*, zurl, -1, MCRAWLER_URL_RES_NAME, le_mcrawler_url);

		if (zend_hash_get_current_key_ex(arr_hash, &key, &keylen, &ind, 0, &pointer) == HASH_KEY_IS_LONG) {
			urls[i]->index = ind;
		} else {
			urls[i]->index = i;
		}
	}
	urls[i] = NULL;

	ZEND_FETCH_RESOURCE(settings, mcrawler_settings*, &zsettings, -1, MCRAWLER_SETTINGS_RES_NAME, le_mcrawler_settings);

	void *buf;
	int buf_sz;

	mcrawler_urls_serialize(urls, settings, &buf, &buf_sz);

	RETVAL_STRINGL(buf, buf_sz, 1);
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

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &buf, &buf_sz) == FAILURE) {
		RETURN_FALSE;
	}

	mcrawler_urls_unserialize(&urls, &settings, buf, buf_sz, emalloc_func);

	array_init(return_value);
	zval *zurls, *zurl;
	zval *zsettings;

	ALLOC_INIT_ZVAL(zurls);
	array_init(zurls);
	add_next_index_zval(return_value, zurls);

	MAKE_STD_ZVAL(zsettings);
	add_next_index_zval(return_value, zsettings);

	for (int i = 0; urls[i]; i++) {
		MAKE_STD_ZVAL(zurl);
		add_index_zval(zurls, urls[i]->index, zurl);
		php_minicrawler_register_url(urls[i], zurl TSRMLS_CC);
	}

	ZEND_REGISTER_RESOURCE(zsettings, settings, le_mcrawler_settings);
}

PHP_FUNCTION(mcrawler_version)
{
	RETURN_STRING(mcrawler_version(), 1);
}

void timing_to_zval(mcrawler_timing *timing, int state, zval *ret)
{
	array_init(ret);
	zval *timingArray;

	if (timing->dnsstart) {
		ALLOC_INIT_ZVAL(timingArray);
		array_init(timingArray);
		add_assoc_string(timingArray, "metric", "DNS Lookup", 1);
		add_assoc_long(timingArray, "value", (timing->dnsend ? timing->dnsend : timing->done) - timing->dnsstart);
		add_next_index_zval(ret, timingArray);
	}

	if (timing->connectionstart) {
		ALLOC_INIT_ZVAL(timingArray);
		array_init(timingArray);
		add_assoc_string(timingArray, "metric", "Initial connection", 1);
		add_assoc_long(timingArray, "value", (timing->requeststart ? timing->requeststart : timing->done) - timing->connectionstart);
		add_next_index_zval(ret, timingArray);
	}

	if (timing->sslstart) {
		ALLOC_INIT_ZVAL(timingArray);
		array_init(timingArray);
		add_assoc_string(timingArray, "metric", "SSL", 1);
		add_assoc_long(timingArray, "value", (timing->sslend ? timing->sslend : timing->done) - timing->sslstart);
		add_next_index_zval(ret, timingArray);
	}

	if (timing->requeststart) {
		ALLOC_INIT_ZVAL(timingArray);
		array_init(timingArray);
		add_assoc_string(timingArray, "metric", "Request", 1);
		add_assoc_long(timingArray, "value", (timing->requestend ? timing->requestend : timing->done) - timing->requeststart);
		add_next_index_zval(ret, timingArray);
	}

	if (timing->requestend) {
		ALLOC_INIT_ZVAL(timingArray);
		array_init(timingArray);
		add_assoc_string(timingArray, "metric", "Waiting", 1);
		add_assoc_long(timingArray, "value", (timing->firstbyte ? timing->firstbyte : timing->done) - timing->requestend);
		add_next_index_zval(ret, timingArray);
	}

	if (timing->firstbyte) {
		ALLOC_INIT_ZVAL(timingArray);
		array_init(timingArray);
		add_assoc_string(timingArray, "metric", "Content download", 1);
		add_assoc_long(timingArray, "value", (timing->lastread && state > MCURL_S_RECVREPLY ? timing->lastread : timing->done) - timing->firstbyte);
		add_next_index_zval(ret, timingArray);
	}

	if (timing->connectionstart) {
		ALLOC_INIT_ZVAL(timingArray);
		array_init(timingArray);
		add_assoc_string(timingArray, "metric", "Total", 1);
		add_assoc_long(timingArray, "value", (timing->lastread && state > MCURL_S_RECVREPLY ? timing->lastread : timing->done) - timing->connectionstart);
		add_next_index_zval(ret, timingArray);
	}
}

PHP_FUNCTION(mcrawler_parse_url)
{
	char *input_s;
	int input_len;
	zval *zbase_url = NULL;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s|z", &input_s, &input_len, &zbase_url) == FAILURE) {
		RETURN_FALSE;
	}

	mcrawler_url_url *url, *base = NULL;
	int base_alloc = 0;

	if (zbase_url) {
		switch (Z_TYPE_P(zbase_url)) {
			case IS_NULL:
				base = NULL;
				break;
			case IS_STRING:
				base = (mcrawler_url_url *)malloc(sizeof(mcrawler_url_url));
				if (mcrawler_url_parse(base, Z_STRVAL_P(zbase_url), NULL) == MCRAWLER_URL_FAILURE) {
					free(base);
					zend_throw_exception_ex(php_mcrawler_url_exception_ce, 0 TSRMLS_CC, "Invalid base URL");
					RETURN_FALSE;
				}
				base_alloc = 1;
				break;
			case IS_RESOURCE:
				ZEND_FETCH_RESOURCE(base, mcrawler_url_url*, &zbase_url, -1, MCRAWLER_URL_URL_RES_NAME, le_mcrawler_url_url);
				break;
			default:
				php_error_docref(NULL TSRMLS_CC, E_ERROR, "Invalid type for base URL, only string or resource allowed.");
				RETURN_FALSE;
		}
	}

	url = emalloc(sizeof(mcrawler_url_url));
	mcrawler_url_parse_state state;

	if (mcrawler_url_parse2(url, input_s, base, &state) == MCRAWLER_URL_FAILURE) {
		efree(url);
		zend_throw_exception_ex(php_mcrawler_url_exception_ce, state TSRMLS_CC, "Invalid URL");
		RETURN_FALSE;
	}

	if (base_alloc) {
		mcrawler_url_free_url(base);
		free(base);
	}

	char *tmp;

	array_init(return_value);

	zval* zurl;
	MAKE_STD_ZVAL(zurl);
	ZEND_REGISTER_RESOURCE(zurl, url, le_mcrawler_url_url);
	add_assoc_resource(return_value, "resource", Z_RESVAL_P(zurl));

	add_assoc_string(return_value, "input", input_s, 1);
	tmp = mcrawler_url_get_href(url);
	add_assoc_string(return_value, "href", tmp, 1);
	free(tmp);
	tmp = mcrawler_url_get_protocol(url);
	add_assoc_string(return_value, "protocol", tmp, 1);
	free(tmp);
	tmp = mcrawler_url_get_username(url);
	add_assoc_string(return_value, "username", tmp, 1);
	free(tmp);
	tmp = mcrawler_url_get_password(url);
	add_assoc_string(return_value, "password", tmp, 1);
	free(tmp);
	char *hostname = emalloc(256);
	mcrawler_url_get_hostname(url, hostname);
	add_assoc_string(return_value, "hostname", hostname, 0);
	char *host = emalloc(256 + 6);
	mcrawler_url_get_host(url, host);
	add_assoc_string(return_value, "host", host, 0);
	tmp = mcrawler_url_get_port(url);
	add_assoc_string(return_value, "port", tmp, 1);
	free(tmp);
	tmp = mcrawler_url_get_pathname(url);
	add_assoc_string(return_value, "pathname", tmp, 1);
	free(tmp);
	tmp = mcrawler_url_get_search(url);
	add_assoc_string(return_value, "search", tmp, 1);
	free(tmp);
	tmp = mcrawler_url_get_hash(url);
	add_assoc_string(return_value, "hash", tmp, 1);
	free(tmp);
}
