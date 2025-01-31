FROM debian:bookworm-slim AS php-minicrawler-dev

ENV LANGUAGE=en_US.UTF-8
ENV LANG=en_US.UTF-8
ENV LC_ALL=C
ENV DEBIAN_FRONTEND=noninteractive
ENV CFLAGS="-O3 -g -fstack-protector-strong"

RUN apt update && apt -qy install \
	# minicrawler dev deps
		libc-ares-dev \
    	zlib1g-dev \
    	libicu-dev \
    	libssl-dev \
		libnghttp2-dev \
	\
	# build tool
    	make \
    	autoconf \
    	automake \
    	autotools-dev \
    	build-essential \
    	libtool \
    	gcc \
    	pkg-config \
	\
	# tools \
		wget \
		curl \
		apt-transport-https \
		ca-certificates \
    	lsb-release  \
    	unzip \
		locales \
		tzdata \
	\
		&& sed -i 's/^.*\(en_US.UTF-8\)/\1/' /etc/locale.gen \
		&& locale-gen \
		&& ln -sf "/usr/share/zoneinfo/Europe/Prague" /etc/localtime  \
    	&& dpkg-reconfigure tzdata \
		&& rm -rf /var/lib/apt/lists/* /var/cache/apt/*

RUN apt-get update \
    && apt-get -y install lsb-release ca-certificates curl \
    && curl -sSLo /tmp/debsuryorg-archive-keyring.deb https://packages.sury.org/debsuryorg-archive-keyring.deb \
    && dpkg -i /tmp/debsuryorg-archive-keyring.deb \
    && sh -c 'echo "deb [signed-by=/usr/share/keyrings/deb.sury.org-php.gpg] https://packages.sury.org/php/ $(lsb_release -sc) main" > /etc/apt/sources.list.d/php.list' \
    && apt-get update \
    && apt install -qy php8.4-dev

# ca-certificates update
RUN sed -i 's/mozilla\/DST_Root_CA_X3.crt/!mozilla\/DST_Root_CA_X3.crt/g' /etc/ca-certificates.conf  \
    && update-ca-certificates \
    && mkdir -p /var/lib/certs \
    && curl --silent --fail --location --show-error --etag-compare etag.txt --etag-save etag.txt --remote-name https://curl.se/ca/cacert.pem \
    && cp -v cacert.pem /var/lib/certs/ca-bundle.crt \
    && cat /etc/ssl/certs/ca-certificates.crt >> ca-bundle.crt \
	 && cp -v ca-bundle.crt /var/lib/certs/ca-bundle.crt

# Install minicrawler and minicrawler libs
COPY --from=dr.brzy.cz/testomato/minicrawler:latest /var/lib/minicrawler/usr /usr
COPY --from=dr.brzy.cz/testomato/minicrawler:latest /var/lib/minicrawler /var/lib/minicrawler

ENV LC_ALL=en_US.UTF-8

RUN echo "extension=minicrawler.so" > /minicrawler.ini

WORKDIR /php-minicrawler
COPY . /php-minicrawler

FROM php-minicrawler-dev AS php-minicrawler-build
RUN phpize || exit 40 \
	&& ./configure || exit 41 \
	&& make INSTALL_ROOT="/var/lib/php-minicrawler" || exit 42 \
	&& mkdir -p /var/lib/php-minicrawler$(php-config --extension-dir) \
	&& install -v modules/*.so /var/lib/php-minicrawler$(php-config --extension-dir) || exit 43 \
	&& mkdir -p /var/lib/php-minicrawler/etc/php/8.4/mods-available \
	&& install -v /minicrawler.ini /var/lib/php-minicrawler/etc/php/8.4/mods-available || exit 44

# Final image with PHP minicrawler extension
FROM debian:bookworm-slim AS php-minicrawler
ENV DEBIAN_FRONTEND=noninteractive
COPY --from=php-minicrawler-build /var/lib/php-minicrawler/usr /var/lib/php-minicrawler/usr
COPY --from=php-minicrawler-build /var/lib/php-minicrawler/etc /var/lib/php-minicrawler/etc