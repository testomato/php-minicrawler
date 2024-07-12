<?php

// Constants definition
define('MCURL_S_JUSTBORN', 0);
define('MCURL_S_PARSEDURL', 1);
define('MCURL_S_INDNS', 2);
define('MCURL_S_GOTIP', 3);
define('MCURL_S_CONNECT', 4);
define('MCURL_S_HANDSHAKE', 5);
define('MCURL_S_GENREQUEST', 6);
define('MCURL_S_SENDREQUEST', 7);
define('MCURL_S_RECVREPLY', 8);
define('MCURL_S_DOWNLOADED', 9);
define('MCURL_S_ERROR', 10);
define('MCURL_S_DONE', 11);

define('MCURL_OPT_NONSSL', 1 << 0);
define('MCURL_OPT_CONVERT_TO_TEXT', 1 << 1);
define('MCURL_OPT_CONVERT_TO_UTF8', 1 << 2);
define('MCURL_OPT_GZIP', 1 << 3);
define('MCURL_OPT_IPV6', 1 << 4);
define('MCURL_OPT_INSECURE', 1 << 5);
define('MCURL_OPT_NOT_FOLLOW_REDIRECTS', 1 << 6);
define('MCURL_OPT_DISABLE_HTTP2', 1 << 7);

define('MCRAWLER_URL_PARSE_STATE_SCHEME_START', 0);
define('MCRAWLER_URL_PARSE_STATE_SCHEME', 1);
define('MCRAWLER_URL_PARSE_STATE_NO_SCHEME', 2);
define('MCRAWLER_URL_PARSE_STATE_SPECIAL_RELATIVE_OR_AUTHORITY', 3);
define('MCRAWLER_URL_PARSE_STATE_PATH_OR_AUTHORITY', 4);
define('MCRAWLER_URL_PARSE_STATE_RELATIVE', 5);
define('MCRAWLER_URL_PARSE_STATE_RELATIVE_SLASH', 6);
define('MCRAWLER_URL_PARSE_STATE_SPECIAL_AUTHORITY_SLASHES', 7);
define('MCRAWLER_URL_PARSE_STATE_SPECIAL_AUTHORITY_IGNORE_SLASHES', 8);
define('MCRAWLER_URL_PARSE_STATE_AUTHORITY', 9);
define('MCRAWLER_URL_PARSE_STATE_HOST', 10);
define('MCRAWLER_URL_PARSE_STATE_HOSTNAME', 11);
define('MCRAWLER_URL_PARSE_STATE_PORT', 12);

/**
 * Initializes a new URL for the crawler.
 *
 * @param string $url The URL to initialize.
 * @param string|null $method The HTTP method to use.
 * @return resource The initialized URL resource.
 */
function mcrawler_init_url($url, $method = null) {
}

/**
 * Initializes new settings for the crawler.
 *
 * @param int|null $timeout The timeout in seconds.
 * @param int|null $delay The delay in milliseconds.
 * @return resource The initialized settings resource.
 */
function mcrawler_init_settings($timeout = null, $delay = null) {
}

/**
 * Closes the specified URL resource.
 *
 * @param resource $url The URL resource to close.
 */
function mcrawler_close_url($url) {
}

/**
 * Closes the specified settings resource.
 *
 * @param resource $settings The settings resource to close.
 */
function mcrawler_close_settings($settings) {
}

/**
 * Retrieves the timeout from the specified settings.
 *
 * @param resource $settings The settings resource.
 * @return int The timeout value.
 */
function mcrawler_get_timeout($settings) {
}

/**
 * Retrieves the delay from the specified settings.
 *
 * @param resource $settings The settings resource.
 * @return int The delay value.
 */
function mcrawler_get_delay($settings) {
}

/**
 * Sets the user agent for the specified URL.
 *
 * @param resource $url The URL resource.
 * @param string $useragent The user agent string.
 */
function mcrawler_set_useragent($url, $useragent) {
}

/**
 * Sets headers for the specified URL.
 *
 * @param resource $url The URL resource.
 * @param string $headers The headers string.
 */
function mcrawler_set_headers($url, $headers) {
}

/**
 * Adds headers to the specified URL.
 *
 * @param resource $url The URL resource.
 * @param string $headers The headers string.
 */
function mcrawler_add_headers($url, $headers) {
}

/**
 * Sets credentials for the specified URL.
 *
 * @param resource $url The URL resource.
 * @param string $username The username.
 * @param string $password The password.
 */
function mcrawler_set_credentials($url, $username, $password) {
}

/**
 * Sets POST data for the specified URL.
 *
 * @param resource $url The URL resource.
 * @param string $postdata The POST data string.
 */
function mcrawler_set_postdata($url, $postdata) {
}


/**
 * Sets the post data for a URL.
 *
 * @param resource $url The URL resource to set post data for.
 * @param string $postdata The post data.
 */
function mcrawler_set_postdata($url, $postdata) {
}

/**
 * Sets options for a URL.
 *
 * @param resource $url The URL resource to set options for.
 * @param int $options The options to set.
 */
function mcrawler_set_options($url, $options) {
}

/**
 * Sets a single option for a URL.
 *
 * @param resource $url The URL resource to set an option for.
 * @param int $option The option to set.
 */
function mcrawler_set_option($url, $option) {
}

/**
 * Sets cookies for a URL.
 *
 * @param resource $url The URL resource to set cookies for.
 * @param string $cookies The cookies to set.
 */
function mcrawler_set_cookies($url, $cookies) {
}

/**
 * Adds cookies to a URL.
 *
 * @param resource $url The URL resource to add cookies to.
 * @param string $cookies The cookies to add.
 */
function mcrawler_add_cookies($url, $cookies) {
}

/**
 * Initiates crawling for the given URLs with specified settings.
 *
 * @param array $urls Array of URL resources to crawl.
 * @param resource $settings The settings resource to use for crawling.
 * @param callable $callback The callback function to execute after crawling.
 */
function mcrawler_go($urls, $settings, $callback) {
}

/**
 * Resets the state of a URL.
 *
 * @param resource $url The URL resource to reset.
 */
function mcrawler_reset($url) {
}

/**
 * Retrieves the index of a URL.
 *
 * @param resource $url The URL resource.
 * @return int The index of the URL.
 */
function mcrawler_get_index($url) {
}

/**
 * Retrieves the last state of a URL.
 *
 * @param resource $url The URL resource.
 * @return int The last state of the URL.
 */
function mcrawler_get_state($url) {
}

/**
 * Retrieves the status of a URL.
 *
 * @param resource $url The URL resource.
 * @return int The status of the URL.
 */
function mcrawler_get_status($url) {
}

/**
 * Retrieves the raw URL string.
 *
 * @param resource $url The URL resource.
 * @return string The raw URL string.
 */
function mcrawler_get_url($url) {
}

/**
 * Retrieves the method used for the URL request.
 *
 * @param resource $url The URL resource.
 * @return string The request method.
 */
function mcrawler_get_method($url) {
}

/**
 * Get the request made to a URL.
 *
 * @param resource $url The URL resource.
 * @return string The request made to the URL.
 */
function mcrawler_get_request($url) {
}

/**
 * Retrieves the URL to which a request was redirected.
 *
 * @param resource $url The URL resource.
 * @return string The URL to which the request was redirected.
 */
function mcrawler_get_redirected_to($url) {
}

/**
 * Retrieves information about redirects.
 *
 * @param resource $url The URL resource.
 * @return array An array containing redirect information.
 */
function mcrawler_get_redirect_info($url) {
}

/**
 * Retrieves the response header.
 *
 * @param resource $url The URL resource.
 * @return string The response header.
 */
function mcrawler_get_header($url) {
}

/**
 * Retrieves the response body.
 *
 * @param resource $url The URL resource.
 * @return string The response body.
 */
function mcrawler_get_body($url) {
}

/**
 * Get the response size of a URL.
 *
 * @param resource $url The URL resource.
 * @return int The response size.
 */
function mcrawler_get_response_size($url) {
}

/**
 * Get the options set for a URL.
 *
 * @param resource $url The URL resource.
 * @return int The options.
 */
function mcrawler_get_options($url) {
}

/**
 * Get timing information for a URL.
 *
 * @param resource $url The URL resource.
 * @return array The timing information.
 */
function mcrawler_get_timing($url) {
}

/**
 * Get cookies associated with a URL.
 *
 * @param resource $url The URL resource.
 * @return string The cookies.
 */
function mcrawler_get_cookies($url) {
}

/**
 * Get the content type of a URL's response.
 *
 * @param resource $url The URL resource.
 * @return string The content type.
 */
function mcrawler_get_content_type($url) {
}

/**
 * Get the charset of a URL's response.
 *
 * @param resource $url The URL resource.
 * @return string The charset.
 */
function mcrawler_get_charset($url) {
}

/**
 * Get the WWW-Authenticate header of a URL's response.
 *
 * @param resource $url The URL resource.
 * @return string The WWW-Authenticate header.
 */
function mcrawler_get_www_authenticate($url) {
}

/**
 * Get the error message associated with a URL's request.
 *
 * @param resource $url The URL resource.
 * @return string The error message.
 */
function mcrawler_get_error_msg($url) {
}

/**
 * Serialize URL and settings objects.
 *
 * @param array $urls Array of URL resources.
 * @param resource $settings The settings resource.
 * @return string The serialized string.
 */
function mcrawler_serialize($urls, $settings) {
}

/**
 * Unserialize a string into URL and settings objects.
 *
 * @param string $serialized_data The serialized string.
 * @return array An array containing the URLs and settings objects.
 */
function mcrawler_unserialize($serialized_data) {
}

/**
 * Get the version of the mcrawler library.
 *
 * @return string The version.
 */
function mcrawler_version() {
}

/**
 * Parse a URL and optionally resolve it against a base URL.
 *
 * @param string $url The URL to parse.
 * @param string|null $base_url Optional base URL to resolve against.
 * @return array Parsed URL components.
 */
function mcrawler_parse_url($url, $base_url = null) {
}