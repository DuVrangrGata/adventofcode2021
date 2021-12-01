#!/bin/sh

set -xe

CFLAGS="-Wall -Werror -std=c++20 -pedantic -ggdb"
LIB=""

g++ $CFLAGS -o main main2.cpp $LIBS
