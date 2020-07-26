#!/bin/bash
CUR_DIR=$PWD
cd ~/src/godot

#MINGW32_PREFIX="/usr/bin/i686-w64-mingw32-"
#MINGW64_PREFIX="/usr/bin/x86_64-w64-mingw32-"

# windows
scons -j8 platform=windows target=release_debug bits=32 use_lto=yes
scons -j8 platform=windows target=release_debug bits=64 use_lto=yes

# x11
scons -j8 platform=x11 target=release_debug bits=32 use_lto=yes
scons -j8 platform=x11 target=release_debug bits=64 use_lto=yes

#osx
scons -j8 platform=osx target=release_debug use_lto=yes osxcross_sdk=darwin19