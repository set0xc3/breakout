#!/bin/sh

cmake -DBUILD_LIB_SHARED= -DCMAKE_BUILD_TYPE=debug -B build
cmake --build build
