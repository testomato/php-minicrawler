--TEST--
Exceptions handling and messages
--FILE--
<?php

try {
	mcrawler_parse_url("https://testomato.com", '');
	user_error('Exception not thrown!!!');
} catch (\McrawlerUrlException $e) {
	if ($e->getCode() !== 0) {
		user_error('Invalid code: ' . $e->getCode());
	}

	if ($e->getMessage() !== 'Invalid base URL') {
		user_error('Invalid message: ' . $e->getMessage());
	}
}

try {
	mcrawler_parse_url("/abcd");
	user_error('Exception not thrown!!!');
} catch (\McrawlerUrlException $e) {
	if ($e->getCode() !== 2) {
		user_error('Invalid code: ' . $e->getCode());
	}

	if ($e->getMessage() !== 'Invalid URL') {
		user_error('Invalid message: ' . $e->getMessage());
	}
}

try {
	mcrawler_parse_url("https://a b");
} catch (\McrawlerUrlException $e) {
	if ($e->getCode() !== 10) {
		user_error('Invalid code: ' . $e->getCode());
	}

	if ($e->getMessage() !== 'Invalid URL') {
		user_error('Invalid message: ' . $e->getMessage());
	}
}

try {
	mcrawler_parse_url("https://testomato.com:80", '');
} catch (\McrawlerUrlException $e) {
	if ($e->getCode() !== 0) {
		user_error('Invalid code: ' . $e->getCode());
	}

	if ($e->getMessage() !== 'Invalid base URL') {
		user_error('Invalid message: ' . $e->getMessage());
	}
}

echo 'OK' . PHP_EOL;
?>
--EXPECT--
OK