--TEST--
Try HTTP authentication
--FILE--
<?php

$url = mcrawler_init_url("https://httpbin.org//basic-auth/admin/password", "GET");
mcrawler_set_credentials($url, "admin", "password");

mcrawler_go([$url], mcrawler_init_settings(), function ($url) {
	$response = json_decode(mcrawler_get_body($url));

	if ($response->authenticated !== true) {
		user_error('Authentication failed');
	}

	echo 'OK' . PHP_EOL;
});

?>
--EXPECT--
OK