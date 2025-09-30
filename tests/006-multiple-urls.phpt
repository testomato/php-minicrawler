--TEST--
Check response for multiple URLs
--FILE--
<?php
$url1 = mcrawler_init_url("https://httpbingo.org", "GET");
$url2 = mcrawler_init_url("https://httpbingo.org/get", "GET");

mcrawler_go([$url1, $url2], mcrawler_init_settings(), function ($url) {

	if (mcrawler_get_method($url) !== 'GET') {
		user_error('Method is not GET');
	}

	if (mcrawler_get_status($url) !== 200) {
		user_error('Status is not 200');
	}

	if (mcrawler_get_redirected_to($url)) {
		user_error('Redirected to another URL');
	}

	echo 'OK' . PHP_EOL;
});
?>
--EXPECT--
OK
OK
