--TEST--
Try download page with GET method
--FILE--
<?php
$url = mcrawler_init_url("https://www.testomato.com/");
$body = mcrawler_get_body($url);

$settings = mcrawler_init_settings();

mcrawler_go([$url], $settings, function ($url) {
	$body = mcrawler_get_body($url);
	echo substr($body, 0, strpos($body, "\n")) . "\n";
});
?>
--EXPECT--
<!DOCTYPE html>