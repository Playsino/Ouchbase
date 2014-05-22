#!/bin/bash

if [ -h $0 ]; then
    realpath="`dirname $0`/`readlink $0`"
    curdir=`dirname $realpath`
else
    curdir=`dirname $0`
fi

cd $curdir/ext
sudo phpize
./configure
make
make install

exists=`php -m | grep ^ouchbase`
echo $exists
if [ -z $exists ]; then
    echo "extension=ouchbase.so" >> `php --ini | grep Loaded | cut -d" " -f12`
fi
