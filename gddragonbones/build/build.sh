#!/bin/bash

# install clang 
cd $OSXCROSS_ROOT/build/llvm-9.0.0.src/build_stage2 && make install
cd $OSXCROSS_ROOT
./build.sh

cd $GODOT_SOURCE_LOCATION

###########################
##      ENGINE FILES     ##
###########################
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

###########################
##      TEMPLATE FILES     ##
###########################

rm -rf bin/

# headless
/usr/local/bin/scons -j8 debug_symbols=no use_static_cpp=yes use_lto=yes platform=server tools=no target=release

#x11
/usr/local/bin/scons -j8 platform=x11 target=release bits=32 use_lto=yes tools=no debug_symbols=no
/usr/local/bin/scons -j8 platform=x11 target=release_debug bits=32 use_lto=yes tools=no debug_symbols=no
/usr/local/bin/scons -j8 platform=x11 target=release bits=64 use_lto=yes tools=no debug_symbols=no
/usr/local/bin/scons -j8 platform=x11 target=release_debug bits=64 use_lto=yes tools=no debug_symbols=no

# windows
/usr/local/bin/scons -j8 platform=windows target=release_debug bits=32 use_lto=yes tools=no debug_symbols=no
/usr/local/bin/scons -j8 platform=windows target=release bits=32 use_lto=yes tools=no debug_symbols=no
/usr/local/bin/scons -j8 platform=windows target=release_debug bits=64 use_lto=yes tools=no debug_symbols=no
/usr/local/bin/scons -j8 platform=windows target=release bits=64 use_lto=yes tools=no debug_symbols=no

#osx
/usr/local/bin/scons -j8 platform=osx target=release_debug osxcross_sdk=darwin19 debug_symbols=no
/usr/local/bin/scons -j8 platform=osx target=release osxcross_sdk=darwin19 debug_symbols=no

# Copy all builds to builds directory
mkdir -p /build/templates
cp -av bin/. /build/templates