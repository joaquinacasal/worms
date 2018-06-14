rm -rf build
mkdir build
cd build
cmake -D INSTALL_PATH=$1 ..
make
make install
