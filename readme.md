# PHP Minicrawler

PHP Minicrawler executes HTTP requests while handling cookies, network connection management and SSL/TLS protocols. By default it follows redirect locations and returns a full response, final URL, parsed cookied and more. It is designed to handle *many* request in parallel in a *single thread* by opening a socket for each connection.

## API documetation

### 

## 3rd party libraries

 * [minicrawler](https://github.com/testomato/minicrawler)
 * asynchronous hostname resolving - [c-ares](http://c-ares.haxx.se/)
 * gzipped content - [zlib](http://zlib.net/)
 * URL parsing and resolving - [uriparser](http://uriparser.sourceforge.net/)
 * TLS/SSL - [OpenSSL](https://www.openssl.org/)

On Linux with `apt-get run apt-get install libc-ares-dev zlib1g-dev liburiparser-dev libssl-dev`

On OS X with homebrew run `brew install c-ares zlib uriparser openssl`

## Build

Tested platforms: Debian Linux, OS X

Install following dependencies (including header files):

 * c-ares
 * zlib1g
 * uriparser
 * OpenSSL (optional)

On Linux with apt-get run `apt-get install libc-ares-dev zlib1g-dev liburiparser-dev libssl-dev`

On OS X with homebrew run `brew install c-ares zlib uriparser openssl`

	phpize
	./configure
	make
	sudo make install
	
Add follow to `minicrawler.ini` or change `php.ini` file and restart PHP:

   [http]
   extension="/usr/local/opt/php56-http/http.so"


## Troubleshooting

Mac OS X sometime use outdated openssl library from X Code source. It's can be fixed with `brew link --force openssl`