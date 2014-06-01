#!/bin/bash

STATUS=""

function build_for {
  CC=$1
  CXX=$2

  BUILD_DIR=build-$CC
  mkdir $BUILD_DIR
  pushd $BUILD_DIR
  CC=$CC CXX=$CXX cmake ../..
  make
  STATUS="$STATUS\n$BUILD_DIR - Status: $?"
  popd
}

if [[ -d builds ]]; then
  rm -rf builds
fi

mkdir builds
pushd builds


# build_for gcc-4.5 g++-4.5
build_for gcc-4.6 g++-4.6
build_for gcc-4.7 g++-4.7
build_for gcc-4.8 g++-4.8
build_for gcc-4.9 g++-4.9
build_for clang clang++
popd

echo "============================================"
echo -e $STATUS
