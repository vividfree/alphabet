#!/bin/sh
curdir=`pwd`
tar zxvf fcgi.tar.gz
prefixdir=$curdir/../fcgi-2.4.1
rm $prefixdir -rf
mkdir -p $prefixdir
cd fcgi-2.4.1-SNAP-0311112127/
./configure prefix=$prefixdir --enable-shared=no
make  && make install
cd ..
rm fcgi-2.4.1-SNAP-0311112127 -rf 
