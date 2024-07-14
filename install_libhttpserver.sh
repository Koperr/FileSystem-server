cd "$(dirname "$0")"

git clone https://github.com/etr/libhttpserver.git
cd libhttpserver
mkdir build
cd build
cmake ..
make
sudo make install