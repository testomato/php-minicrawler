--TEST--
Parsing different URL
--FILE--
<?php

{
	$href = mcrawler_parse_url("/abcd", "https://testomato.com")['href'];
	if ($href !== "https://testomato.com/abcd") {
		user_error('Invalid URL from base_url: ' . $href);
	}
}

{
	$href = mcrawler_parse_url("https://testomato.com:81", null)['href'];
	if ($href !== "https://testomato.com:81/") {
		user_error('Invalid URL with port: ' . $href);
	}
}

{
	$resource = mcrawler_parse_url("https://testomato.com:8080");
	if ($resource['href'] !== "https://testomato.com:8080/") {
		user_error('Invalid URL with port: ' . $resource['href']);
	}
	// from resource
	$href = mcrawler_parse_url("/r", $resource['resource'])['href'];

	if ($href !== "https://testomato.com:8080/r") {
		user_error('Invalid URL from resource: ' . $href);
	}
}

echo 'OK' . PHP_EOL;
?>
--EXPECT--
OK