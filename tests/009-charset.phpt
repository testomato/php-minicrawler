--TEST--
Charset and content type
--FILE--
<?php
$web = mcrawler_init_url("https://testomato.com/", "GET");

mcrawler_go([$web], mcrawler_init_settings(), function ($url) {

	if (mcrawler_get_charset($url) !== 'UTF-8') {
		user_error('Charset is not UTF-8 but ' . mcrawler_get_charset($url));
	}

	if (mcrawler_get_content_type($url) !== 'text/html') {
		user_error('Content type is not text/html but ' . mcrawler_get_content_type($url));
	}

	if (!mcrawler_get_body($url)) {
		user_error('Body is empty');
	}

	echo 'OK' . PHP_EOL;
});
?>
--EXPECT--
OK