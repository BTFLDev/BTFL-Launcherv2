#!/bin/sh

set -xe

BUILD_TYPE=$1
BUILD_DIR=build/$1

cmake -G "Unix Makefiles" . -B $BUILD_DIR -DCMAKE_BUILD_TYPE=$BUILD_TYPE
cp $BUILD_DIR/compile_commands.json compile_commands.json
cmake --build $BUILD_DIR
open $BUILD_DIR/BTFL-Launcher.app
