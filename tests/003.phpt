--TEST--
Try mcrawler_init_url with different methods
--FILE--
<?php
$resource = mcrawler_init_url('http://www.google.com'); // default GET
echo mcrawler_get_method($resource) . PHP_EOL;

$resource = mcrawler_init_url('http://www.google.com', "GET");
echo mcrawler_get_method($resource) . PHP_EOL;

$resource = mcrawler_init_url('http://www.google.com', "POST");
echo mcrawler_get_method($resource) . PHP_EOL;

$resource = mcrawler_init_url('http://www.google.com', "PUT");
echo mcrawler_get_method($resource) . PHP_EOL;

$resource = mcrawler_init_url('http://www.google.com', "DELETE");
echo mcrawler_get_method($resource) . PHP_EOL;
?>
--EXPECT--
GET
GET
POST
PUT
DELETE