#!/bin/bash

# This is the top file called

# Steps:

# clean/create build dir
rm -rf ./build
mkdir -p ./build

#docker build --build-arg UBUNTU_VERSION="16.04" . -t godot-dragonbones:x11
docker build . -t godot-dragonbones:other

# Build clients-v dragonbonesDir:/build -v /home/ozzadar/src/osxcross:/osxcross 
#docker run -v dragonbonesDir:/build -v /home/ozzadar/src/osxcross:/osxcross -it godot-dragonbones:x11
docker run -v dragonbonesDir:/build -v /home/ozzadar/src/osxcross:/osxcross -it godot-dragonbones:other
