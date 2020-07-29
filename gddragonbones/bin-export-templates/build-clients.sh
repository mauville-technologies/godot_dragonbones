#!/bin/bash

# Steps:
docker build . -t godot-dragonbones:templates

# build templates
# replace these volumes with 1 folder and the built and compiled osxcross (build.sh build_clang.sh)
docker run -v /home/ozzadar/src/dragonbonesDir:/build -v /home/ozzadar/src/osxcross:/osxcross -it godot-dragonbones:templates
