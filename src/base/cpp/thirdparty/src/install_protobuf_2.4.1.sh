#!/bin/sh
curdir=`pwd`
tar zxvf  protobuf-2.4.1.tar.gz
prefixdir=$curdir/../protobuf-2.4.1
rm $prefixdir -rf
mkdir -p $prefixdir
cd protobuf-2.4.1
./configure --prefix=$prefixdir --enable-shared=no
make && make install
cd ..
rm protobuf-2.4.1 -rf 
