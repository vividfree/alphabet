#!/bin/sh
curdir=`pwd`
tar zxvf cityhash.tar.gz
prefixdir=$curdir/../cityhash
rm $prefixdir -rf
mkdir -p $prefixdir
cd cityhash
./configure prefix=$prefixdir --enable-shared=no
make  && make install
cd ..
rm cityhash -rf 
