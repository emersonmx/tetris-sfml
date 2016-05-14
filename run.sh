#!/bin/bash

set -e

BUILD_DIR=build
EXECUTABLE=tetris
BUILD_TYPE=Debug

if [[ $# == 1 ]]; then
    BUILD_TYPE=Release
fi

echo "Create \"$BUILD_DIR\" path"
mkdir -p $BUILD_DIR
pushd build > /dev/null

echo "Configuring..."
cmake -DCMAKE_BUILD_TYPE=$BUILD_TYPE ..

echo "Building in $BUILD_TYPE mode..."
make -j3
popd > /dev/null

echo "Running..."
$BUILD_DIR/$EXECUTABLE
echo "Done."

echo "Generating tags"
ctags --c++-kinds=+p --c-kinds=+p --fields=+liaS --extra=+fq -R /usr/include/SFML src/
echo "Done."
