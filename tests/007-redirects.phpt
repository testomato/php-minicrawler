--TEST--
Check response for multiple URLs
--FILE--
<?php
$url = mcrawler_init_url("https://httpbin.org/redirect-to?url=https://www.testomato.com", "GET");

mcrawler_go([$url], mcrawler_init_settings(), function ($url) {

	if (mcrawler_get_redirected_to($url) !== 'https://www.testomato.com/') {
		user_error('Invalid redirect url:' . mcrawler_get_redirected_to($url));
	}

	// get first redirect info

	$info = (object) current(mcrawler_get_redirect_info($url));

	if ($info->url !== 'https://www.testomato.com/') {
		user_error('Invalid redirect url:' . $info->url);
	}

	if ($info->status !== 302) {
		user_error('Invalid http code:' . $info->status);
	}

	echo 'OK' . PHP_EOL;
});
?>
--EXPECT--
OK