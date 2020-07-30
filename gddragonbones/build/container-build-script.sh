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

# Package .app
cp -r misc/dist/osx_tools.app ./Godot-dragonbones-3.2.50.app
mkdir -p Godot-dragonbones-3.2.50.app/Contents/MacOS
mv bin/*osx.opt.tools* Godot-dragonbones-3.2.50.app/Contents/MacOS/Godot
chmod +x Godot-dragonbones-3.2.50.app/Contents/MacOS/Godot
zip -r -y /build/engine Godot-dragonbones-3.2.50.app

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

# osx
/usr/local/bin/scons -j8 platform=osx target=release_debug osxcross_sdk=darwin19 debug_symbols=no
/usr/local/bin/scons -j8 platform=osx target=release osxcross_sdk=darwin19 debug_symbols=no

# Copy all builds to builds directory
mkdir -p /build/templates

# move headless first
mv bin/*server.* /build/templates

# rename to expected format and move to expected folder
mkdir -p bin/templates
mv bin/*x11.opt.debug.32* bin/templates/linux_x11_32_debug
mv bin/*x11.opt.debug.64* bin/templates/linux_x11_64_debug
mv bin/*x11.opt.32* bin/templates/linux_x11_32_release
mv bin/*x11.opt.64* bin/templates/linux_x11_32_release

mv bin/*windows.opt.debug.32* bin/templates/windows_32_debug.exe
mv bin/*windows.opt.debug.64* bin/templates/windows_64_debug.exe
mv bin/*windows.opt.32* bin/templates/windows_32_release.exe
mv bin/*windows.opt.64* bin/templates/windows_64_release.exe

# Package .app
cp -r misc/dist/osx_tools.app ./osx_template.app
# put the proper plist in there
rm misc/dist/osx_tools.app/Contents/Info.plist
mv misc/dist/osx_tools.app/Contents/Info-templates.plist misc/dist/osx_tools.app/Contents/Info.plist

mkdir -p bin/osx_template.app/Contents/MacOS
mv bin/*osx.opt.debug.64* ./bin/osx_template.app/Contents/MacOS/godot_osx_debug.64
mv bin/*osx.opt.64* ./bin/osx_template.app/Contents/MacOS/godot_osx_release.64
chmod +x ./bin/osx_template.app/Contents/MacOS/godot_osx_debug.64
chmod +x ./bin/osx_template.app/Contents/MacOS/godot_osx_release.64
zip -r -y bin/osx.zip ./bin/osx_template.app

rm bin/*osx.opt*
rm -rf bin/osx_template.app

# Add version.txt
echo "3.2.50.stable" > bin/version.txt

# zip file
mv bin templates
zip -r godot-dragonbones-templates.zip templates

# persist
cp -v godot-dragonbones-templates.zip /build/templates