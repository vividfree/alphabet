#!/bin/sh

#sh ./install_libunwind_1.1.sh

if [ $? -eq 0 ]; then
	curdir=`pwd`
	tar zxvf glog-0.3.3.tar.gz
	prefixdir=$curdir/../glog-0.3.3
	rm $prefixdir -rf
	mkdir -p $prefixdir
	cd glog-0.3.3
  export CXXFLAGS=-fPIC 
#	export CPPFLAGS=-I../../libunwind-1.1/include
#	export LDFLAGS=-L../../libunwind-1.1/lib
	./configure prefix=$prefixdir --enable-shared=no
	make  && make install
	cd ..
	rm glog-0.3.3 -rf 
else
	echo "[FATAL]Failed to install libunwind, which is required for installing glog"
fi
