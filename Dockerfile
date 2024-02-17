FROM gcc:13.2.0

RUN apt-get update && apt-get install -y cmake ninja-build


WORKDIR /usr/src/myapp
RUN --mount=type=bind,source=code,target=/source set -ex && cmake -G"Ninja" /source/
