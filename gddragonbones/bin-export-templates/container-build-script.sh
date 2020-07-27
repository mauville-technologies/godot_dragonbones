#!/bin/bash

echo "BUILDING WITH UBUNTU VERSION ${1}"

if [ "$1" = "16.04"]
then
    # x11
    /usr/local/bin/scons -j8 platform=x11 tools=no target=release bits=32 use_lto=yes
    /usr/local/bin/scons -j8 platform=x11 tools=no target=release_debug bits=32 use_lto=yes
    /usr/local/bin/scons -j8 platform=x11 tools=no target=release bits=64 use_lto=yes
    /usr/local/bin/scons -j8 platform=x11 tools=no target=release_debug bits=64 use_lto=yes
else
    # windows
    /usr/local/bin/scons -j8 platform=windows tools=no target=release_debug bits=32 use_lto=yes
    /usr/local/bin/scons -j8 platform=windows tools=no target=release bits=32 use_lto=yes
    /usr/local/bin/scons -j8 platform=windows tools=no target=release_debug bits=64 use_lto=yes
    /usr/local/bin/scons -j8 platform=windows tools=no target=release bits=64 use_lto=yes
    
    #osx
    /usr/local/bin/scons -j8 platform=osx tools=no target=release use_lto=yes osxcross_sdk=darwin19
    /usr/local/bin/scons -j8 platform=osx tools=no target=release_debug use_lto=yes osxcross_sdk=darwin19
fi

# Copy all builds to builds directory
cp -avr ./bin/. /build