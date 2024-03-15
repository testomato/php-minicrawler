# PHP Minicrawler

PHP Minicrawler executes HTTP requests while handling cookies, network connection management and SSL/TLS protocols.
By default, it follows redirect locations and returns a full response, final URL, parsed cookies and more.
It is designed to handle *many* request in parallel in a *single thread* by opening a socket for each connection.

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

## Building php-minicralwer container

```shell
SOURCE_COMMIT=$(git rev-parse --short HEAD) \
docker buildx bake --file docker-bake.hcl php-minicrawler --print # show what will be build
```

How to add other tags:

```shell
docker buildx bake \
	--file docker-bake.hcl\
	--set php-minicrawler.tags.COMMIT="dr.brzy.cz/testomato/php-minicralwer:$(git rev-parse --short HEAD)" \
	--set php-minicrawler.tags.COMMIT="dr.brzy.cz/testomato/php-minicralwer:v5.2.6" \
	--set php-minicrawler.tags.COMMIT="dr.brzy.cz/testomato/php-minicralwer:latest" \
	--print
	# --push
```

## Try PHP minicrawler

First you need pull minicrawler image:

```shell
docker pull dr.brzy.cz/testomato/php-minicrawler:latest

# or Debian bookworm
docker pull dr.brzy.cz/testomato/php-minicrawler:bokworm

# or specific minicrawler version
docker pull dr.brzy.cz/testomato/php-minicrawler:v5.2.6
```

then run it

```shell
docker run -it dr.brzy.cz/testomato/php-minicrawler:bookworm /bin/bash
```

Inside container run `./minicrawler5`

## Install minicrawler to your image

```dockerfile
COPY --from=dr.brzy.cz/testomato/php-minicrawler:latest /var/lib/php-minicrawler/usr /usr
COPY --from=dr.brzy.cz/testomato/php-minicrawler:latest /var/lib/php-minicrawler/etc /etc
RUN phpenmod minicrawler
```

Command `phpenmod` require `php-common` package to be installed.

## Links

* https://gitlab.int.wikidi.net/testomato/php-minicrawler
* https://github.com/testomato/minicrawler
