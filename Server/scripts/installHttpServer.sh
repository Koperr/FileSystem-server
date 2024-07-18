git clone https://github.com/etr/libhttpserver.git
cd libhttpserver

./bootstrap
mkdir build
cd build
../configure
make
make install