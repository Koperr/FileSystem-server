#!/bin/sh

# Usuń istniejący katalog build, jeśli istnieje
rm -rf build

mkdir build
cd build

cmake -DCMAKE_CXX_FLAGS="-I/usr/include" .. || exit 1

# Uruchom CMake
#cmake .. || exit 1

# Zbuduj projekt
make || exit 1

cd ..
cd bin/Linux/Debug || exit 1
./Server