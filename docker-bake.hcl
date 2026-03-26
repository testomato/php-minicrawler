# Define the Docker Compose services block
# https://docs.docker.com/build/bake/reference/

####################################################################################################
# docker buildx bake --file docker-bake.hcl php-minicrawler --push --no-cache --progress=plain
####################################################################################################

target "php-minicrawler" {
  context    = "."
  dockerfile = ".docker/Dockerfile"
  target     = "php-minicrawler"
  platforms  = ["linux/amd64", "linux/arm64"]
  pull       = true
  tags       = [
    "gitlab.int.wikidi.net:5050/testomato/php-minicrawler:latest",
    "gitlab.int.wikidi.net:5050/testomato/php-minicrawler:v5.2.7"
  ]
}

####################################################################################################
# docker buildx bake --file docker-bake.hcl --push --no-cache --progress=plain
####################################################################################################

group "default" {
  targets = ["php-minicrawler"]
}