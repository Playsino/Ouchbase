rm -rf ext
zephir compile
cd ext
sudo phpize
./configure
make
make install
