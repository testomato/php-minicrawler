<?php

// Constants definition
const MCURL_S_JUSTBORN = 0;
const MCURL_S_PARSEDURL = 1;
const MCURL_S_INDNS = 2;
const MCURL_S_GOTIP = 3;
const MCURL_S_CONNECT = 4;
const MCURL_S_HANDSHAKE = 5;
const MCURL_S_GENREQUEST = 6;
const MCURL_S_SENDREQUEST = 7;
const MCURL_S_RECVREPLY = 8;
const MCURL_S_DOWNLOADED = 9;
const MCURL_S_ERROR = 10;
const MCURL_S_DONE = 11;

const MCURL_OPT_NONSSL = 1 << 0;
const MCURL_OPT_CONVERT_TO_TEXT = 1 << 1;
const MCURL_OPT_CONVERT_TO_UTF8 = 1 << 2;
const MCURL_OPT_GZIP = 1 << 3;
const MCURL_OPT_IPV6 = 1 << 4;
const MCURL_OPT_INSECURE = 1 << 5;
const MCURL_OPT_NOT_FOLLOW_REDIRECTS = 1 << 6;
const MCURL_OPT_DISABLE_HTTP2 = 1 << 7;

const MCRAWLER_URL_PARSE_STATE_SCHEME_START = 0;
const MCRAWLER_URL_PARSE_STATE_SCHEME = 1;
const MCRAWLER_URL_PARSE_STATE_NO_SCHEME = 2;
const MCRAWLER_URL_PARSE_STATE_SPECIAL_RELATIVE_OR_AUTHORITY = 3;
const MCRAWLER_URL_PARSE_STATE_PATH_OR_AUTHORITY = 4;
const MCRAWLER_URL_PARSE_STATE_RELATIVE = 5;
const MCRAWLER_URL_PARSE_STATE_RELATIVE_SLASH = 6;
const MCRAWLER_URL_PARSE_STATE_SPECIAL_AUTHORITY_SLASHES = 7;
const MCRAWLER_URL_PARSE_STATE_SPECIAL_AUTHORITY_IGNORE_SLASHES = 8;
const MCRAWLER_URL_PARSE_STATE_AUTHORITY = 9;
const MCRAWLER_URL_PARSE_STATE_HOST = 10;
const MCRAWLER_URL_PARSE_STATE_HOSTNAME = 11;
const MCRAWLER_URL_PARSE_STATE_PORT = 12;

/**
 * Initializes a new URL for the crawler.
 *
 * @param string $url the URL to initialize
 * @param string|null $method the HTTP method to use
 * @return resource the initialized URL resource
 */
function mcrawler_init_url(string $url, ?string $method = null) {}

/**
 * Initializes new settings for the crawler.
 *
 * @param int|null $timeout the timeout in seconds
 * @param int|null $delay the delay in milliseconds
 * @return resource the initialized settings resource
 */
function mcrawler_init_settings(?int $timeout = null, ?int $delay = null) {}

/**
 * Closes the specified URL resource.
 *
 * @param resource $url the URL resource to close
 */
function mcrawler_close_url($url): void {}

/**
 * Closes the specified settings resource.
 *
 * @param resource $settings the settings resource to close
 */
function mcrawler_close_settings($settings): void {}

/**
 * Retrieves the timeout from the specified settings.
 *
 * @param resource $settings the settings resource
 * @return int the timeout value
 */
function mcrawler_get_timeout($settings): int {}

/**
 * Retrieves the delay from the specified settings.
 *
 * @param resource $settings the settings resource
 * @return int the delay value
 */
function mcrawler_get_delay($settings): int {}

/**
 * Retrieves the user agent for the specified URL.
 *
 * @param resource $url the URL resource
 * @return string|null the user agent string or null if not set
 */
function mcrawler_get_useragent($url): ?string {}

/**
 * Sets the user agent for the specified URL.
 *
 * @param resource $url the URL resource
 * @param string $useragent the user agent string
 */
function mcrawler_set_useragent($url, string $useragent): void {}

/**
 * Sets headers for the specified URL.
 *
 * @param resource $url the URL resource
 * @param string $headers the headers string
 */
function mcrawler_set_headers($url, string $headers): void {}

/**
 * Adds headers to the specified URL.
 *
 * @param resource $url the URL resource
 * @param string $headers the headers string
 */
function mcrawler_add_headers($url, string $headers): void {}

/**
 * Sets credentials for the specified URL.
 *
 * @param resource $url the URL resource
 * @param string $username the username
 * @param string $password the password
 */
function mcrawler_set_credentials($url, string $username, string $password): void {}

/**
 * Sets POST data for the specified URL.
 *
 * @param resource $url the URL resource
 * @param string $postdata the POST data string
 */
function mcrawler_set_postdata($url, string $postdata): void {}

/**
 * Sets options for a URL.
 *
 * @param resource $url the URL resource to set options for
 * @param int $options the options to set
 */
function mcrawler_set_options($url, int $options): void {}

/**
 * Sets a single option for a URL.
 *
 * @param resource $url the URL resource to set an option for
 * @param int $option the option to set
 */
function mcrawler_set_option($url, int $option): void {}

/**
 * Sets cookies for a URL.
 *
 * @param resource $url the URL resource to set cookies for
 * @param string $cookies the cookies to set
 */
function mcrawler_set_cookies($url, string $cookies): void {}

/**
 * Adds cookies to a URL.
 *
 * @param resource $url the URL resource to add cookies to
 * @param string $cookies the cookies to add
 */
function mcrawler_add_cookies($url, string $cookies): void {}

/**
 * Initiates crawling for the given URLs with specified settings.
 *
 * @param array $urls array of URL resources to crawl
 * @param resource $settings the settings resource to use for crawling
 * @param callable $callback the callback function to execute after crawling
 */
function mcrawler_go(array $urls, $settings, callable $callback): void {}

/**
 * Resets the state of a URL.
 *
 * @param resource $url the URL resource to reset
 */
function mcrawler_reset($url): void {}

/**
 * Retrieves the index of a URL.
 *
 * @param resource $url the URL resource
 * @return int the index of the URL
 */
function mcrawler_get_index($url): int {}

/**
 * Retrieves the last state of a URL.
 *
 * @param resource $url the URL resource
 * @return int the last state of the URL
 */
function mcrawler_get_state($url): int {}

/**
 * Retrieves the status of a URL.
 *
 * @param resource $url the URL resource
 * @return int the status of the URL
 */
function mcrawler_get_status($url): int {}

/**
 * Retrieves the raw URL string.
 *
 * @param resource $url the URL resource
 * @return string the raw URL string
 */
function mcrawler_get_url($url): string {}

/**
 * Retrieves the method used for the URL request.
 *
 * @param resource $url the URL resource
 * @return string the request method
 */
function mcrawler_get_method($url): string {}

/**
 * Get the request made to a URL.
 *
 * @param resource $url the URL resource
 * @return string the request made to the URL
 */
function mcrawler_get_request($url): string {}

/**
 * Retrieves the URL to which a request was redirected.
 *
 * @param resource $url the URL resource
 * @return string the URL to which the request was redirected
 */
function mcrawler_get_redirected_to($url): string {}

/**
 * Retrieves information about redirects.
 *
 * @param resource $url the URL resource
 * @return array an array containing redirect information
 */
function mcrawler_get_redirect_info($url): array {}

/**
 * Retrieves the response header.
 *
 * @param resource $url the URL resource
 * @return string the response header
 */
function mcrawler_get_header($url): string {}

/**
 * Retrieves the response body.
 *
 * @param resource $url the URL resource
 * @return string the response body
 */
function mcrawler_get_body($url): string {}

/**
 * Get the response size of a URL.
 *
 * @param resource $url the URL resource
 * @return int the response size
 */
function mcrawler_get_response_size($url): int {}

/**
 * Get the options set for a URL.
 *
 * @param resource $url the URL resource
 * @return int the options
 */
function mcrawler_get_options($url): int {}

/**
 * Get timing information for a URL.
 *
 * @param resource $url the URL resource
 * @return array the timing information
 */
function mcrawler_get_timing($url): array {}

/**
 * Get cookies associated with a URL.
 *
 * @param resource $url the URL resource
 * @return string the cookies
 */
function mcrawler_get_cookies($url): string {}

/**
 * Get the content type of a URL's response.
 *
 * @param resource $url the URL resource
 * @return string the content type
 */
function mcrawler_get_content_type($url): string {}

/**
 * Get the charset of a URL's response.
 *
 * @param resource $url the URL resource
 * @return string the charset
 */
function mcrawler_get_charset($url): string {}

/**
 * Get the WWW-Authenticate header of a URL's response.
 *
 * @param resource $url the URL resource
 * @return string the WWW-Authenticate header
 */
function mcrawler_get_www_authenticate($url): string {}

/**
 * Get the error message associated with a URL's request.
 *
 * @param resource $url the URL resource
 * @return string the error message
 */
function mcrawler_get_error_msg($url): string {}

/**
 * Serialize URL and settings objects.
 *
 * @param array $urls array of URL resources
 * @param resource $settings the settings resource
 * @return string the serialized string
 */
function mcrawler_serialize(array $urls, $settings): string {}

/**
 * Unserialize a string into URL and settings objects.
 *
 * @param string $serialized_data the serialized string
 * @return array an array containing the URLs and settings objects
 */
function mcrawler_unserialize(string $serialized_data): array {}

/**
 * Get the version of the mcrawler library.
 *
 * @return string the version
 */
function mcrawler_version(): string {}

/**
 * Parse a URL and optionally resolve it against a base URL.
 *
 * @param string $url the URL to parse
 * @param string|null $base_url optional base URL to resolve against
 * @return array parsed URL components
 */
function mcrawler_parse_url(string $url, ?string $base_url = null): array {}

/**
 * Class McrawlerException
 * Represents a general exception for mcrawler operations.
 */
class McrawlerException extends Exception {}

/**
 * Class McrawlerUrlException
 * Represents an exception for URL processing in mcrawler.
 */
class McrawlerUrlException extends McrawlerException {}
