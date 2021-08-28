ARG UBUNTU_VERSION=18.04
FROM ubuntu:$UBUNTU_VERSION
ARG UBUNTU_VERSION

SHELL ["/bin/bash", "-c"]
RUN set +H

# needed for mac builds
ENV GODOT_VERSION="tags/3.3.3-stable"
ENV GODOT_DRAGONBONES_VERSION="3.3.51"
ENV GODOT_DRAGONBONES_BRANCH="master"
ENV OSXCROSS_ROOT="/osxcross"
ENV GODOT_SOURCE_LOCATION="/godot"
ENV EMSCRIPTEN_LOCATION="/emscripten"
ENV EMSCRIPTEN_VERSION=1.39.20
ENV ANDROID_HOME="/AndroidSDK"
ENV ANDROID_SDK_ROOT="/AndroidSDK"
ENV DEBIAN_FRONTEND="noninteractive"
ENV UNATTENDED=true

# install software propertoes
RUN apt update && apt -y install software-properties-common

# install python 3
RUN apt-get update \
  && apt-get install -y python3-pip python3-dev \
  && cd /usr/local/bin \
  && ln -s /usr/bin/python3 python \
  && pip3 install --upgrade pip

# x11 32bit deps
RUN dpkg --add-architecture i386 && \
    apt update && \
    apt -y install \
        gcc-multilib libx11-6:i386 libxrandr-dev:i386 libxinerama-dev:i386 libxxf86vm-dev:i386 libxcursor-dev:i386 \
        libxi-dev:i386 libasound2-dev:i386 libpulse-dev:i386 libgl1-mesa-dev:i386 wget

# get dependencies
RUN apt update \
    && apt -y install \
# linux deps
    build-essential scons pkg-config libx11-dev libxcursor-dev libxinerama-dev \
    libgl1-mesa-dev libglu-dev libasound2-dev libpulse-dev libudev-dev libxi-dev libxrandr-dev yasm \
    git gcc-multilib g++-multilib libxcursor-dev zip libxml2-dev libssl-dev \
# windows deps
    mingw-w64 libstdc++6 libc6-dev-i386 libc6-dev \
#osx deps
    cmake patch

    RUN update-alternatives --set i686-w64-mingw32-gcc /usr/bin/i686-w64-mingw32-gcc-posix && \
    update-alternatives --set i686-w64-mingw32-g++ /usr/bin/i686-w64-mingw32-g++-posix && \
    update-alternatives --set x86_64-w64-mingw32-gcc /usr/bin/x86_64-w64-mingw32-gcc-posix && \
    update-alternatives --set x86_64-w64-mingw32-g++ /usr/bin/x86_64-w64-mingw32-g++-posix

# mono deps
    # RUN apt -y install gnupg ca-certificates && \
    # apt-key adv --keyserver hkp://keyserver.ubuntu.com:80 --recv-keys 3FA7E0328081BFF6A14DA29AA6A19B38D3D831EF && \
    # echo "deb https://download.mono-project.com/repo/ubuntu stable-bionic main" | tee /etc/apt/sources.list.d/mono-official-stable.list && \
    # apt update && apt -y install mono-devel

    # RUN curl -LO https://curl.haxx.se/ca/cacert.pem && cert-sync --user cacert.pem

# configure scons
RUN python -m pip install scons && \
    # change first line of scons file to python 3
    sed -i '1s/\#!\/usr\/local\/bin\/python/\#!\/usr\/bin\/python3/' /usr/local/bin/scons

# android deps ?
RUN apt -y install default-jdk

RUN mkdir -p $ANDROID_HOME/cmdline-tools && \
    wget -O AndroidSDK.zip https://dl.google.com/android/repository/commandlinetools-linux-6609375_latest.zip && \
    unzip AndroidSDK.zip -d ${ANDROID_HOME}/cmdline-tools && \
    yes | ${ANDROID_HOME}/cmdline-tools/tools/bin/sdkmanager --licenses && \
    ${ANDROID_HOME}/cmdline-tools/tools/bin/sdkmanager --sdk_root=$ANDROID_SDK_ROOT "platform-tools" "build-tools;30.0.1" "platforms;android-29" "cm
dline-tools;latest" "cmake;3.10.2.4988404"

# iphone deps ?

# GET EMSCRIPTEN
RUN git clone --progress https://github.com/emscripten-core/emsdk.git $EMSCRIPTEN_LOCATION
WORKDIR ${EMSCRIPTEN_LOCATION}

RUN ./emsdk install $EMSCRIPTEN_VERSION && ./emsdk activate $EMSCRIPTEN_VERSION && source ./emsdk_env.sh

# GET GODOT 3.2 SOURCE
RUN git clone --progress --verbose https://github.com/godotengine/godot.git $GODOT_SOURCE_LOCATION

# CHECKOUT CORRECT RELEASE BRANCH
WORKDIR ${GODOT_SOURCE_LOCATION}
RUN git checkout ${GODOT_VERSION}

WORKDIR ${GODOT_SOURCE_LOCATION}/modules

# GET GODOT-DRAGONBONES SOURCE
RUN git clone --progress --verbose https://github.com/mauville-technologies/godot_dragonbones.git
WORKDIR ${GODOT_SOURCE_LOCATION}/modules/godot_dragonbones
RUN git checkout ${GODOT_DRAGONBONES_BRANCH}

WORKDIR ${GODOT_SOURCE_LOCATION}

COPY ./js-no-rtti-patch.patch .
RUN git apply js-no-rtti-patch.patch

COPY ./android-no-rtti-patch.patch .
RUN git apply android-no-rtti-patch.patch

# COPY BUILD SCRIPT
COPY ./container-build-script.sh .
RUN chmod +x container-build-script.sh

# COPY GODOT-DRAGONBONES VERSION
RUN rm version.py
COPY ./version.py .

# BUILD THE THINGS
# PROFIT

RUN echo $UBUNTU_VERSION
ENV UBUNTU_VERSIONS=$UBUNTU_VERSION
CMD ./container-build-script.sh $UBUNTU_VERSIONS
