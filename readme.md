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

## Building php-minicrawler container

```shell
docker buildx bake --file docker-bake.hcl php-minicrawler --push # --no-cache --print
```

How to add other tags:

```shell
docker buildx bake \
  --file docker-bake.hcl \
  --set php-minicrawler.tags.COMMIT="dr.brzy.cz/testomato/php-minicrawler:$(git rev-parse --short HEAD)" \
  --set php-minicrawler.tags.COMMIT="dr.brzy.cz/testomato/php-minicrawler:v5.2.7" \
  --set php-minicrawler.tags.COMMIT="dr.brzy.cz/testomato/php-minicrawler:latest" \
  --push
```

## Try PHP minicrawler

Pull latest image and run it:

```shell
docker pull dr.brzy.cz/testomato/php-minicrawler:latest
docker run -it --rm dr.brzy.cz/testomato/php-minicrawler:latest /bin/bash
```

then you can try to install minicrawler locally inside container:

```shell
# install php 8.4
# check https://packages.sury.org/php/README.txt for more info
apt-get update
apt-get -y install lsb-release ca-certificates curl
curl -sSLo /tmp/debsuryorg-archive-keyring.deb https://packages.sury.org/debsuryorg-archive-keyring.deb
dpkg -i /tmp/debsuryorg-archive-keyring.deb
sh -c 'echo "deb [signed-by=/usr/share/keyrings/deb.sury.org-php.gpg] https://packages.sury.org/php/ $(lsb_release -sc) main" > /etc/apt/sources.list.d/php.list'
apt-get update
apt install -qy php8.4-cli

# install minicrawler
cp -r /var/lib/php-minicrawler/usr /
cp -r /var/lib/php-minicrawler/etc /
phpenmod minicrawler

```

then run interactive php shell:

```shell
php -a
```

and try 

## Test & Development

```shell
docker compose build php-minicrawler-dev
docker compose run --rm php-minicrawler-dev /bin/bash
````

Inside container run:

```shell
phpize
./configure
make INSTALL_ROOT="/var/lib/php-minicrawler"

# install minicrawler.so
install -v modules/*.so $(php-config --extension-dir)

# install minicrawler.ini
install -v /minicrawler.ini /etc/php/8.4/mods-available

# enable minicrawler
phpenmod minicrawler
```

or just run `./rebuild` script inside container.

After that you can run `php -m | grep minicrawler` to see if minicrawler is enabled.
Then you can run tests:

```shell
make test
```

## Install minicrawler into your image

```dockerfile
COPY --from=dr.brzy.cz/testomato/php-minicrawler:latest /var/lib/php-minicrawler/usr /usr
COPY --from=dr.brzy.cz/testomato/php-minicrawler:latest /var/lib/php-minicrawler/etc /etc
RUN phpenmod minicrawler
```

Command `phpenmod` require `php-common` package to be installed.

## Links

* https://gitlab.int.wikidi.net/testomato/php-minicrawler
* https://github.com/testomato/minicrawler
