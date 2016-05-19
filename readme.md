# PHP Minicrawler

PHP Minicrawler executes HTTP requests while handling cookies, network connection management and SSL/TLS protocols. By default it follows redirect locations and returns a full response, final URL, parsed cookied and more. It is designed to handle *many* request in parallel in a *single thread* by opening a socket for each connection.

## Build

Tested platforms: Debian Linux, OS X

Build and install [minicrawler](https://github.com/testomato/minicrawler) first.

Then run:

```
phpize
./configure
make
sudo make install
```

Add following to `minicrawler.ini` or change `php.ini` file and restart PHP:

```
[minicrawler]
extension="/usr/local/opt/php-minicrawler/modules/minicrawler.so"
```