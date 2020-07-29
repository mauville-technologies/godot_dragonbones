#!/bin/bash

apt -y remove clang
cd $OSXCROSS_ROOT/build/llvm-9.0.0.src/build_stage2 && make install
cd $OSXCROSS_ROOT
./build.sh

cd $GODOT_SOURCE_LOCATION

/usr/local/bin/scons -j8 platform=x11 target=release_debug bits=32 use_lto=yes
/usr/local/bin/scons -j8 platform=x11 target=release_debug bits=64 use_lto=yes

# windows
/usr/local/bin/scons -j8 platform=windows target=release_debug bits=32 use_lto=yes
/usr/local/bin/scons -j8 platform=windows target=release_debug bits=64 use_lto=yes

#osx
/usr/local/bin/scons -j8 platform=osx target=release_debug osxcross_sdk=darwin19

# Copy all builds to builds directory
mkdir -p /build/engine
cp -av bin/. /build/engine
