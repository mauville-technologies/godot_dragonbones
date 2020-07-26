FROM ubuntu:16.04

# get dependencies
RUN apt update \
    && apt -y install \
# linux deps
    build-essential scons pkg-config libx11-dev libxcursor-dev libxinerama-dev \
    libgl1-mesa-dev libglu-dev libasound2-dev libpulse-dev libudev-dev libxi-dev libxrandr-dev yasm \
# windows deps
    mingw-w64

# set up osxcross