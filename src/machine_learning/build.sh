#!/bin/bash

# package script
# Author: vividfree (vividfree@qq.com)
#  Date : 2015-12-30

rm target -rf

cd src && ./build_src.sh && cd ../

if [ $? -eq 0 ]; then
	mkdir -p target

	cd python && python ./pipeline_setup.py bdist_egg && cd ../
	
	if [ $? -eq 0 ]; then
		cp bin target -rf
		cp conf target -rf
		cp python target -rf
		cp shell target -rf

   cd target && tar cjvf ../ftrl.tar.bz2 . && cd ../
	fi
fi
