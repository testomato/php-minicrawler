<?php
$url = mcrawler_init_url("http://testomato.com");
$settings = mcrawler_init_settings();
mcrawler_go([$url], $settings);
var_dump(mcrawler_get_status($url));
var_dump(mcrawler_get_timing($url));
