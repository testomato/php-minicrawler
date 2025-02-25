--TEST--
Try download HTML page
--FILE--
<?php
$url = mcrawler_init_url("https://www.testomato.com/");

mcrawler_go([$url], mcrawler_init_settings(), function ($url) {
	$body = mcrawler_get_body($url);
	if (str_starts_with($body, '<!DOCTYPE html>') === false) {
		user_error('Invalid HTML response');
	}

	echo 'OK' . PHP_EOL;
});
?>
--EXPECT--
OK