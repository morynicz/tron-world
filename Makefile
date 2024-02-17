PROJECT=tron-world

all: build run

build:
	sudo docker buildx build -t ${PROJECT} --build-context code=`pwd`/code .

run:
	sudo docker run --mount type=bind,source=`pwd`/code,target=/source,readonly -it sfml_docker

test:
	sudo docker run --mount type=bind,source=`pwd`/code,target=/source,readonly -it sfml_docker ninja run_tests

.PHONY: all build run
