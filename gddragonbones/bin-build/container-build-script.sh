#!/bin/bash

if [ "$1" = "16.04" ]
then
    echo "BUILDING WITH UBUNTU VERSION ${1}"

    # x11
    /usr/local/bin/scons -j8 platform=x11 target=release_debug bits=32 use_lto=yes
    /usr/local/bin/scons -j8 platform=x11 target=release_debug bits=64 use_lto=yes
else
    echo "BUILDING WITH UBUNTU VERSION ${1}"

    # windows
    /usr/local/bin/scons -j8 platform=windows target=release_debug bits=32 use_lto=yes
    /usr/local/bin/scons -j8 platform=windows target=release_debug bits=64 use_lto=yes

    #osx
    /usr/local/bin/scons -j8 platform=osx target=release_debug use_lto=yes osxcross_sdk=darwin19
fi

# Copy all builds to builds directory
cp -av bin/. /build/engine