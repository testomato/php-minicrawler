# PHP Minicrawler

PHP Minicrawler executes HTTP requests while handling cookies, network connection management and SSL/TLS protocols. By default it follows redirect locations and returns a full response, final URL, parsed cookied and more. It is designed to handle *many* request in parallel in a *single thread* by opening a socket for each connection.

## 3rd party libraries

 * [minicrawler](https://github.com/testomato/minicrawler)
 * asynchronous hostname resolving - [c-ares](http://c-ares.haxx.se/)
 * gzipped content - [zlib](http://zlib.net/)
 * URL parsing and resolving - [uriparser](http://uriparser.sourceforge.net/)
 * TLS/SSL - [OpenSSL](https://www.openssl.org/)

Follow [minicrawler Build instruction](https://github.com/testomato/minicrawler/blob/wheezy/README.md#build)

## Build

Tested platforms: Debian Linux, OS X

Install following dependencies (including header files, i.e. dev packages):

 * c-ares
 * zlib1g
 * uriparser
 * OpenSSL (optional)

On Linux with apt-get run:

```
apt-get install libc-ares-dev zlib1g-dev liburiparser-dev libssl-dev
```

On OS X with [homebrew](http://brew.sh/) run:

```
brew install c-ares zlib openssl uriparser
brew link c-ares zlib openssl uriparser --force
```

Then run:

```
phpize
./configure
make
sudo make install
```

On OS X with homebrew `CFLAGS` and `LDFLAGS` need to contain proper paths. You can assign them directly as the configure script options.

```
 ./configure CFLAGS="-I/usr/local/include" LDFLAGS="-L/usr/local/opt -L/usr/local/lib"
```

Add follow to `minicrawler.ini` or change `php.ini` file and restart PHP:

```
[minicrawler]
extension="/usr/local/opt/php-minicrawler/modules/minicrawler.so"
```
