--TEST--
Response size check
--FILE--
<?php
$png = mcrawler_init_url("https://httpbin.org/image/png", "GET");

mcrawler_go([$png], mcrawler_init_settings(), function ($url) {


	if (mcrawler_get_response_size($url) < 1000) {
		user_error('Response size is too small');
	}

	if (mcrawler_get_content_type($url) !== 'image/png') {
		user_error('Content type is not image/png but ' . mcrawler_get_content_type($url));
	}

	echo 'OK' . PHP_EOL;
});
?>
--EXPECT--
OK