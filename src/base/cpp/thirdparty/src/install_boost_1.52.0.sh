#!/bin/sh
curdir=`pwd`
tar xjvf  boost_1_52_0.tar.bz2
prefixdir=$curdir/../boost_1.52.0
rm $prefixdir -rf
mkdir -p $prefixdir
cd boost_1_52_0
./bootstrap.sh && ./bjam install  link=static variant=release threading=multi --prefix=$prefixdir --with-program_options --with-thread --with-system  --with-filesystem --with-regex
cd ..
rm boost_1_52_0 -rf 
