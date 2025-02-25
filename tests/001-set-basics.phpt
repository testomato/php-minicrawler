--TEST--
Init URL settings
--FILE--
<?php
$url = mcrawler_init_url('https://www.example.com');
mcrawler_set_useragent($url, 'test');
mcrawler_set_headers($url, 'X-A: B' . "\r\n");
mcrawler_add_headers($url, 'X-C: D' . "\r\n");
mcrawler_set_credentials($url, 'user', 'pass');
mcrawler_set_postdata($url, 'xxx');
mcrawler_set_option($url, \MCURL_OPT_GZIP | \MCURL_OPT_INSECURE);

echo 'OK';
?>
--EXPECT--
OK