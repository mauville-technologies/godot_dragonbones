FROM ubuntu:16.04

# needed for mac builds
ENV GODOT_VERSION="3.2"
ENV OSXCROSS_ROOT="/osxcross"
ENV GODOT_SOURCE_LOCATION="/godot"
ENV GODOT_GD_LOCATION="/godot-dragonbones"

# get dependencies
RUN apt update \
    && apt -y install \
# linux deps
    build-essential scons pkg-config libx11-dev libxcursor-dev libxinerama-dev \
    libgl1-mesa-dev libglu-dev libasound2-dev libpulse-dev libudev-dev libxi-dev libxrandr-dev yasm \
    git \
# windows deps
    mingw-w64
# android deps ?

# iphone deps ?

# set up osxcross
# COPY TO CONTAINER
COPY osxcross/ $OSXCROSS_ROOT

# GET GODOT 3.2 SOURCE
RUN git clone https://github.com/godotengine/godot.git $GODOT_SOURCE_LOCATION

# CHECKOUT CORRECT RELEASE BRANCH
WORKDIR ${GODOT_SOURCE_LOCATION}
RUN git checkout ${GODOT_VERSION}

# GET GODOT-DRAGONBONES SOURCE
RUN git clone https://github.com/mauville-technologies/godot-dragonbones.git $GODOT_GD_LOCATION

# PUT THEM WHERE THEY BELONG
RUN cp -avr ${GODOT_GD_LOCATION}/gddragonbones ${GODOT_SOURCE_LOCATION}/modules/


# COPY BUILD SCRIPT
COPY ./container-build-script.sh .
RUN chmod +x container-build-script.sh

# BUILD THE THINGS
# PROFIT
CMD ["./container-build-script.sh"]