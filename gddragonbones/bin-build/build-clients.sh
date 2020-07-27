#!/bin/bash

# This is the top file called

# Steps:

# clean/create build dir
rm -rf ./build
mkdir -p ./build

docker build --build-arg UBUNTU_VERSION="16.04" . -t godot-dragonbones:x11
docker build . -t godot-dragonbones:other

# Build clients
docker run -v dragonbonesDir:/build -it godot-dragonbones:x11
docker run -v dragonbonesDir:/build -it godot-dragonbones:other