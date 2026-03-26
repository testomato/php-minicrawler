# PHP Minicrawler

PHP Minicrawler executes HTTP requests while handling cookies, network connection management and SSL/TLS protocols.
By default, it follows redirect locations and returns a full response, final URL, parsed cookies and more.
It is designed to handle *many* request in parallel in a *single thread* by opening a socket for each connection.

## Usage

### 1. Login to GitLab Container Registry

Use [group deploy token](https://gitlab.int.wikidi.net/groups/testomato/-/settings/repository#js-deploy-tokens):

```shell
docker login gitlab.int.wikidi.net:5050 -u testomato -p "gldt-Y4KWxV-8bx5Mh4NZWVKp"
```

### 2. Pull image

```shell
docker pull gitlab.int.wikidi.net:5050/testomato/php-minicrawler:latest
```

### 3. Run

```shell
docker run -it --rm gitlab.int.wikidi.net:5050/testomato/php-minicrawler:latest /bin/bash
```

### Install minicrawler into your image

```dockerfile
COPY --from=gitlab.int.wikidi.net:5050/testomato/php-minicrawler:latest /var/lib/php-minicrawler/usr /usr
COPY --from=gitlab.int.wikidi.net:5050/testomato/php-minicrawler:latest /var/lib/php-minicrawler/etc /etc
RUN phpenmod minicrawler
```

Command `phpenmod` require `php-common` package to be installed.

## Build from source

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
  --set php-minicrawler.tags.COMMIT="gitlab.int.wikidi.net:5050/testomato/php-minicrawler:$(git rev-parse --short HEAD)" \
  --set php-minicrawler.tags.COMMIT="gitlab.int.wikidi.net:5050/testomato/php-minicrawler:v5.2.7" \
  --set php-minicrawler.tags.COMMIT="gitlab.int.wikidi.net:5050/testomato/php-minicrawler:latest" \
  --push
```

## Test & Development

```shell
docker compose build php-minicrawler-dev
docker compose run --rm php-minicrawler-dev /bin/bash
```

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

## Links

* https://gitlab.int.wikidi.net/testomato/php-minicrawler
* https://github.com/testomato/minicrawler
