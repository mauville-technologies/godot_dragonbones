ARG UBUNTU_VERSION=19.04
FROM ubuntu:$UBUNTU_VERSION

ARG UBUNTU_VERSION
SHELL ["/bin/bash", "-c"]
RUN set +H

# needed for mac builds
ENV GODOT_VERSION="3.2"
ENV OSXCROSS_ROOT="/osxcross"
ENV GODOT_SOURCE_LOCATION="/godot"
ENV GODOT_GD_LOCATION="/godot-dragonbones"

# install python 3
RUN apt-get update \
  && apt-get install -y python3-pip python3-dev \
  && cd /usr/local/bin \
  && ln -s /usr/bin/python3 python \
  && pip3 install --upgrade pip

# get dependencies
RUN apt update \
    && apt -y install \
# linux deps
    build-essential scons pkg-config libx11-dev libxcursor-dev libxinerama-dev \
    libgl1-mesa-dev libglu-dev libasound2-dev libpulse-dev libudev-dev libxi-dev libxrandr-dev yasm \
    git \
# windows deps
    mingw-w64 libstdc++6 libc6-dev-i386 libc6-dev && \
    update-alternatives --set i686-w64-mingw32-gcc /usr/bin/i686-w64-mingw32-gcc-posix && \
    update-alternatives --set i686-w64-mingw32-g++ /usr/bin/i686-w64-mingw32-g++-posix && \
    update-alternatives --set x86_64-w64-mingw32-gcc /usr/bin/x86_64-w64-mingw32-gcc-posix && \
    update-alternatives --set x86_64-w64-mingw32-g++ /usr/bin/x86_64-w64-mingw32-g++-posix

# configure scons
RUN python -m pip install scons && \
    # change first line of scons file to python 3
    sed -i '1s/\#!\/usr\/local\/bin\/python/\#!\/usr\/bin\/python3/' /usr/local/bin/scons

    
# android deps ?

# iphone deps ?

# GET GODOT 3.2 SOURCE
RUN git clone https://github.com/godotengine/godot.git $GODOT_SOURCE_LOCATION

# CHECKOUT CORRECT RELEASE BRANCH
WORKDIR ${GODOT_SOURCE_LOCATION}
RUN git checkout ${GODOT_VERSION}

# GET GODOT-DRAGONBONES SOURCE
RUN git clone https://github.com/mauville-technologies/godot-dragonbones.git $GODOT_GD_LOCATION

# PUT THEM WHERE THEY BELONG
RUN cp -ar ${GODOT_GD_LOCATION}/gddragonbones ${GODOT_SOURCE_LOCATION}/modules/


# COPY BUILD SCRIPT
COPY ./container-build-script.sh .
RUN chmod +x container-build-script.sh

# set up osxcross
# COPY TO CONTAINER
COPY osxcross/ $OSXCROSS_ROOT

# BUILD THE THINGS
# PROFIT

CMD ["./container-build-script.sh", "${UBUNTU_VERSION}"]