<?php
echo "version: " . mcrawler_version() . "\n";

$url1 = mcrawler_init_url("https://testomato.com");

$settings = mcrawler_init_settings(7, 70);

mcrawler_go([$url1], $settings, function () {});
mcrawler_go([$url1], $settings, function () {});
mcrawler_reset($url1);
mcrawler_go([$url1], $settings, function () {});
