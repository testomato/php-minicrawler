<?php
echo "version: " . mcrawler_version() . "\n";

$url = mcrawler_init_url("http://testomato.com");

//test default params
$settings = mcrawler_init_settings();
mcrawler_close_settings($settings);

$settings = mcrawler_init_settings(7, 70);
mcrawler_go([$url], $settings);
var_dump(mcrawler_get_status($url));
var_dump(mcrawler_get_timing($url));
mcrawler_close_settings($settings);
mcrawler_close_url($url);
