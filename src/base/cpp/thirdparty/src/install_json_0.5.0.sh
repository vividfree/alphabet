#!/bin/sh
curdir=`pwd`
tar zxvf  jsoncpp-src-0.5.0.tar.gz
prefixdir=$curdir/../jsoncpp-0.5.0
rm $prefixdir -rf
mkdir -p $prefixdir/lib
cd jsoncpp-src-0.5.0
scons platform=linux-gcc
cp include $prefixdir -r
# Note by Jun:
# 	Usually we use name of libjson.a to indicate the library of json4cpp.
#	However, in K1 tools/bidurl_benchmark, we use libjson as well as json4cpp, and they have library name conflict, that's
#	why we copy another library of json4cpp with name libjsoncpp.a.
#	It is ugly but it works and currently it doesn't have any negative impact.
cp libs/linux-gcc-4.8.5/libjson_linux-gcc-4.8.5_libmt.a $prefixdir/lib/libjson.a
cp libs/linux-gcc-4.8.5/libjson_linux-gcc-4.8.5_libmt.a $prefixdir/lib/libjsoncpp.a
cd ..
rm jsoncpp-src-0.5.0 -rf 
