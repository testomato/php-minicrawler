<?php
echo "version: " . mcrawler_version() . "\n";

$url1 = mcrawler_init_url("http://testomato.com");
mcrawler_set_useragent($url1, 'test');
mcrawler_set_headers($url1, 'X-A: B');
mcrawler_set_credentials($url1, 'user', 'pass');
mcrawler_set_postdata($url1, 'xxx');

$url2 = mcrawler_init_url("http://wikidi.com");

//test default params
$settings = mcrawler_init_settings();
mcrawler_close_settings($settings);

$settings = mcrawler_init_settings(7, 70);
echo "Timeout: ";
var_dump(mcrawler_get_timeout($settings));
echo "Delay: ";
var_dump(mcrawler_get_delay($settings));

mcrawler_go([$url1, $url2], $settings, function ($url) {var_dump(mcrawler_get_timing($url)); sleep(2);});
echo "1: status: ";
var_dump(mcrawler_get_status($url1));
echo "2: status: ";
var_dump(mcrawler_get_status($url2));

echo "1: cookies: ";
var_dump($cookies = mcrawler_get_cookies($url1));
mcrawler_set_cookies($url1, $cookies);

$data = mcrawler_serialize([$url1, 3 => $url2], $settings);
mcrawler_close_settings($settings);
mcrawler_close_url($url1);
mcrawler_close_url($url2);

var_dump($r = mcrawler_unserialize($data));
mcrawler_close_url($r[0][0]);
