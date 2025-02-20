<?php

$url = mcrawler_init_url("https://www.ozana.cz/");
$body = mcrawler_get_body($url);

$settings = mcrawler_init_settings();

mcrawler_go([$url], $settings, function ($url) {
	$body = mcrawler_get_body($url);
	echo $body; // download website content
});