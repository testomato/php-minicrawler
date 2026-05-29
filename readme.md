# PHP Minicrawler

`php-minicrawler` is a PHP extension that executes HTTP requests with support for:

- cookies
- connection management
- SSL/TLS
- automatic redirect following

It is optimized for many parallel requests in a single thread by using one socket per connection.

## Quick Start (Docker image)

### 1) Log in to GitLab Container Registry

Use a [group deploy token](https://gitlab.int.wikidi.net/groups/testomato/-/settings/repository#js-deploy-tokens):

```shell
docker login gitlab.int.wikidi.net:5050 -u testomato -p "$GITLAB_DEPLOY_TOKEN"
```

### 2) Pull image

```shell
docker pull gitlab.int.wikidi.net:5050/testomato/php-minicrawler:latest
```

### 3) Run container

```shell
docker run -it --rm gitlab.int.wikidi.net:5050/testomato/php-minicrawler:latest /bin/bash
```

## Use in Your Own Image

```dockerfile
COPY --from=gitlab.int.wikidi.net:5050/testomato/php-minicrawler:latest /var/lib/php-minicrawler/usr /usr
COPY --from=gitlab.int.wikidi.net:5050/testomato/php-minicrawler:latest /var/lib/php-minicrawler/etc /etc
RUN phpenmod minicrawler
```

`phpenmod` requires the `php-common` package.

## Build from Source

Tested on Debian Linux and macOS.

1. Build and install [minicrawler](https://github.com/testomato/minicrawler) first.
2. Build this extension:

```shell
phpize
./configure
make
sudo make install
```

Then add the extension to `minicrawler.ini` (or `php.ini`) and restart PHP:

```ini
[minicrawler]
extension="/usr/local/opt/php-minicrawler/modules/minicrawler.so"
```

## Build and Publish Container

Build and push the default image:

```shell
docker buildx bake --file docker-bake.hcl php-minicrawler --push
```

Build and push multiple tags:

```shell
docker buildx bake \
  --file docker-bake.hcl \
  --set php-minicrawler.tags.COMMIT="gitlab.int.wikidi.net:5050/testomato/php-minicrawler:$(git rev-parse --short HEAD)" \
  --set php-minicrawler.tags.COMMIT="gitlab.int.wikidi.net:5050/testomato/php-minicrawler:v5.2.7" \
  --set php-minicrawler.tags.COMMIT="gitlab.int.wikidi.net:5050/testomato/php-minicrawler:latest" \
  --push
```

## Development and Testing

Start development container:

```shell
docker compose build php-minicrawler-dev
docker compose run --rm php-minicrawler-dev /bin/bash
```

Inside the container:

```shell
phpize
./configure
make INSTALL_ROOT="/var/lib/php-minicrawler"

# install minicrawler.so
install -v modules/*.so "$(php-config --extension-dir)"

# install minicrawler.ini
install -v /minicrawler.ini /etc/php/8.5/mods-available

# enable minicrawler
phpenmod minicrawler
```

Alternative: run `./rebuild` inside the container.

Verify extension is enabled:

```shell
php -m | grep minicrawler
```

Run tests:

```shell
make test
```

## Links

- https://gitlab.int.wikidi.net/testomato/php-minicrawler
- https://github.com/testomato/minicrawler
