#!/bin/bash

# This is the top file called

# Steps:

# clean/create build dir
rm -rf ./build
mkdir -p ./build

# Build docker image
docker build . -t godot-dragonbones:local

# Run docker image
docker run -v ./build:/build -it godot-dragonbones:local