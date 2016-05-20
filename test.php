<?php
echo "version: " . mcrawler_version() . "\n";

$url1 = mcrawler_init_url("https://testomato.com");
mcrawler_set_useragent($url1, 'test');
mcrawler_set_headers($url1, 'X-A: B' . "\r\n");
mcrawler_add_headers($url1, 'X-C: D' . "\r\n");
mcrawler_set_credentials($url1, 'user', 'pass');
mcrawler_set_postdata($url1, 'xxx');
mcrawler_set_option($url1, \MCURL_OPT_GZIP | \MCURL_OPT_INSECURE);

$url2 = mcrawler_init_url("http://wikidi.com/");

//test default params
$settings = mcrawler_init_settings();
mcrawler_close_settings($settings);

$settings = mcrawler_init_settings(7, 70);
echo "Timeout: ";
var_dump(mcrawler_get_timeout($settings));
echo "Delay: ";
var_dump(mcrawler_get_delay($settings));

mcrawler_go([$url1, $url2], $settings, function ($url) {var_dump(mcrawler_get_timing($url)); sleep(0);});
echo "1: options: ";
var_dump(mcrawler_get_options($url1));
echo "1: status: ";
var_dump(mcrawler_get_status($url1));
echo "2: status: ";
var_dump(mcrawler_get_status($url2));

echo "1: index: ";
var_dump(mcrawler_get_index($url1));
echo "1: state: ";
var_dump(mcrawler_get_state($url1));
echo "1: method: ";
var_dump(mcrawler_get_method($url1));
echo "1: request: ";
var_dump(mcrawler_get_request($url1));
echo "1: redirected_to: ";
var_dump(mcrawler_get_redirected_to($url1));
echo "1: redirect_info: ";
var_dump(mcrawler_get_redirect_info($url1));
echo "1: header: ";
var_dump(mcrawler_get_header($url1));
echo "1: body: ";
var_dump(substr(mcrawler_get_body($url1), 0, 50) . '...');
echo "1: response_size: ";
var_dump(mcrawler_get_response_size($url1));
echo "1: cookies: ";
var_dump($cookies = mcrawler_get_cookies($url1));
mcrawler_set_cookies($url1, $cookies);
echo "1: content_type: ";
var_dump(mcrawler_get_content_type($url1));
echo "1: charset: ";
var_dump(mcrawler_get_charset($url1));
echo "1: www-autheticate: ";
var_dump(mcrawler_get_www_authenticate($url1));
echo "1: error_msg: ";
var_dump(mcrawler_get_error_msg($url1));

$data = mcrawler_serialize([$url1, 3 => $url2], $settings);
mcrawler_close_settings($settings);
mcrawler_close_url($url1);
mcrawler_close_url($url2);

var_dump($r = mcrawler_unserialize($data));
mcrawler_close_url($r[0][0]);

var_dump(mcrawler_parse_url("/abcd", "http://testomato.com"));
var_dump(mcrawler_parse_url("http://testomato.com:81", NULL));
var_dump($t = mcrawler_parse_url("http://testomato.com:82"));
var_dump(mcrawler_parse_url("/r", $t['resource']));
try {
	mcrawler_parse_url("/abcd");
} catch (\McrawlerUrlException $e) {
	echo $e->getCode() . ': ' . $e->getMessage() . "\n";
}
try {
	mcrawler_parse_url("http://a b");
} catch (\McrawlerUrlException $e) {
	echo $e->getCode() . ': ' . $e->getMessage() . "\n";
}
