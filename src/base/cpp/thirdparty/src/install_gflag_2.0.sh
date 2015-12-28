#!/bin/sh
curdir=`pwd`
tar zxvf gflags-2.0.tar.gz
prefixdir=$curdir/../gflags-2.0
rm $prefixdir -rf
mkdir -p $prefixdir
cd gflags-2.0
./configure prefix=$prefixdir --enable-shared=no
make  && make install
cd ..
rm gflags-2.0 -rf 
