#!/bin/sh
curdir=`pwd`
unzip gtest-1.6.0.zip
prefixdir=$curdir/../gtest-1.6.0
rm $prefixdir -rf
mkdir -p $prefixdir/lib
mkdir -p $prefixdir/include
cd gtest-1.6.0
./configure prefix=$prefixdir --enable-shared=no
make 
cp lib/.libs/libgtest.a $prefixdir/lib
cp include/gtest $prefixdir/include/ -r
cd ..
rm gtest-1.6.0 -rf 
