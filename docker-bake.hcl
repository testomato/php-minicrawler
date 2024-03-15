# Define the Docker Compose services block
# https://docs.docker.com/build/bake/reference/

####################################################################################################
# docker buildx bake --file docker-bake.hcl php-minicralwer --push --no-cache --progress=plain
####################################################################################################

target "php-minicralwer" {
  context    = "."
  dockerfile = "Dockerfile"
  platforms  = ["linux/amd64", "linux/arm64"]
  pull       = true
  tags       = [
    "dr.brzy.cz/testomato/php-minicralwer:latest"
  ]
}

####################################################################################################
# docker buildx bake --file docker-bake.hcl --push --no-cache --progress=plain
####################################################################################################

group "default" {
  targets = ["php-minicralwer"]
}