#!/bin/bash
rm target -rf

cd src && ./build_src.sh && cd ../

if [ $? -eq 0 ]; then
	mkdir -p target

	cd python && python ./pipeline_setup.py bdist_egg && cd ../
	
	if [ $? -eq 0 ]; then
		cp conf target -rf
		cp data target -rf
		cp python target -rf
		cp shell target -rf

   cd target && tar cjvf ../analyse_lianjia.tar.bz2 . && cd ../
	fi
fi
