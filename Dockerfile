FROM debian:bookworm-slim

ENV LANGUAGE en_US.UTF-8
ENV LANG en_US.UTF-8
ENV LC_ALL C
ENV DEBIAN_FRONTEND noninteractive
ENV CFLAGS "-O3 -g -fstack-protector-strong"

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

# Install php5.6-dev package
RUN wget -O /etc/apt/trusted.gpg.d/php.gpg https://packages.sury.org/php/apt.gpg  \
    && echo "deb https://packages.sury.org/php/ $(lsb_release -sc) main" > /etc/apt/sources.list.d/php.list  \
    && apt update \
    && apt install -qy php5.6-dev

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

ENV LC_ALL en_US.UTF-8

RUN echo "extension=minicrawler.so" > /minicrawler.ini

WORKDIR /php-minicrawler
COPY . /php-minicrawler

RUN phpize || exit 40 \
	&& ./configure || exit 41 \
	&& make INSTALL_ROOT="/var/lib/php-minicrawler" || exit 42 \
	&& mkdir -p /var/lib/php-minicrawler$(php-config --extension-dir) \
	&& install -v modules/*.so /var/lib/php-minicrawler$(php-config --extension-dir) || exit 43 \
	&& mkdir -p /var/lib/php-minicrawler/etc/php/5.6/mods-available \
	&& install -v /minicrawler.ini /var/lib/php-minicrawler/etc/php/5.6/mods-available || exit 44
