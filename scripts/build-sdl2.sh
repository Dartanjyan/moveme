#!/bin/bash

###
# Set HOST variable to Windows if you want to build this library for the Window
# with x86_64-w64-mingw32. Or else it will be built for linux.
#
# For example: HOST=Windows ./scripts/build-sdl2.sh
###
set -e

SCRIPT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )"
SDL_DIR="$(realpath ${SCRIPT_DIR}/..)/3rdparty/SDL2"
SRC_DIR="${SDL_DIR}/src"
INSTALL_DIR="${SDL_DIR}/install"

CONFIG_FLAGS="--prefix=$INSTALL_DIR"

mkdir -pv $SDL_DIR

if [[ ! -d $SRC_DIR ]]; then
    git clone --depth=1 https://github.com/libsdl-org/SDL.git -b SDL2 $SRC_DIR
fi

cd $SRC_DIR
rm -rf build
mkdir -v build
cd build

if [[ $HOST != "" ]] then
    CONFIG_FLAGS="$CONFIG_FLAGS --host=$HOST"
fi

../configure $CONFIG_FLAGS

make
make install

