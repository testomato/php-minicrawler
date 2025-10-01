--TEST--
Get user agent
--FILE--
<?php
$url = mcrawler_init_url('https://www.example.com');

// Test getting user agent when not set (should return null)
var_dump(mcrawler_get_useragent($url));

// Set user agent
mcrawler_set_useragent($url, 'My Custom Agent');

// Test getting user agent after setting
echo 'User agent: ' . mcrawler_get_useragent($url) . "\n";

mcrawler_close_url($url);
?>
--EXPECT--
NULL
User agent: My Custom Agent
