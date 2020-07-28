#!/bin/bash

# This is the top file called

# Steps:
docker build . -t godot-dragonbones:x11

# Build clients-v dragonbonesDir:/build -v /home/ozzadar/src/osxcross:/osxcross 
docker run -v dragonbonesDir:/build -v /home/ozzadar/src/osxcross:/osxcross -it godot-dragonbones:x11
