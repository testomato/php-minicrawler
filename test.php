<?php
echo "version: " . mcrawler_version() . "\n";

$url = mcrawler_init_url("http://testomato.com");
mcrawler_set_useragent($url, 'test');
mcrawler_set_headers($url, 'X-A: B');
mcrawler_set_credentials($url, 'user', 'pass');
mcrawler_set_postdata($url, 'xxx');

//test default params
$settings = mcrawler_init_settings();
mcrawler_close_settings($settings);

$settings = mcrawler_init_settings(7, 70);
mcrawler_go([$url], $settings);
var_dump(mcrawler_get_status($url));
var_dump(mcrawler_get_timing($url));
mcrawler_close_settings($settings);
mcrawler_close_url($url);
