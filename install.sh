#!/bin/bash

cd ext
sudo phpize
./configure
make
make install

exists=`php -m | grep ^ouchbase`
echo $exists
if [ -z $exists]; then
    echo "extension=ouchbase.so" >> `php --ini | grep Loaded | cut -d" " -f12`
fi
