--TEST--
Default timeout settings
--FILE--
<?php
$settings = mcrawler_init_settings(7, 70);
echo 'Timeout: ' . mcrawler_get_timeout($settings) . "\n";
echo 'Delay: ' . mcrawler_get_delay($settings);
mcrawler_close_settings($settings);
?>
--EXPECT--
Timeout: 7
Delay: 70