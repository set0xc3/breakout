#!/bin/sh

cmake -DCMAKE_SYSTEM_NAME=Windows \
      -DCMAKE_C_COMPILER=i686-w64-mingw32-gcc \
      -DCMAKE_CXX_COMPILER=i686-w64-mingw32-g++ \
      -DCMAKE_BUILD_TYPE=debug \
      -DCMAKE_PREFIX_PATH=build \
      -B build

cmake --build build
