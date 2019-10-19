#!/bin/bash

FILE_IN=$argc[1]
FILE_OUT=$argc[2]
test -d build || mkdir build
cd build
cmake -G"Unix Makefiles" ..
make
cd ../bin/
chmod +x main

