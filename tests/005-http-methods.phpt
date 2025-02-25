--TEST--
Try GET, POST, PUT and DELETE methods
--FILE--
<?php
$resource = mcrawler_init_url('https://httpbin.org/get', "GET");
if (mcrawler_get_method($resource) !== 'GET') {
	user_error('Method is not GET');
}

$resource = mcrawler_init_url('https://httpbin.org/post', "POST");
if (mcrawler_get_method($resource) !== 'POST') {
	user_error('Method is not POST');
}

$resource = mcrawler_init_url('https://httpbin.org/put', "PUT");
if (mcrawler_get_method($resource) !== 'PUT') {
	user_error('Method is not PUT');
}

$resource = mcrawler_init_url('https://httpbin.org/delete', "DELETE");
if (mcrawler_get_method($resource) !== 'DELETE') {
	user_error('Method is not DELETE');
}

$settings = mcrawler_init_settings();
$resource = mcrawler_init_url('https://httpbin.org/get'); // default GET
mcrawler_go([$resource], $settings, function ($url) {

	if (mcrawler_get_method($url) !== 'GET') {
		user_error('Method is not GET');
	}

	$json = json_decode(mcrawler_get_body($url));
	if (json_last_error() !== JSON_ERROR_NONE) {
		user_error('Invalid JSON response');
	}

	if ($json->url !== 'https://httpbin.org/get') {
		user_error('Incorrect or missing URL');
	}

	mcrawler_close_url($url);
	echo 'OK' . PHP_EOL;
});

?>
--EXPECT--
OK