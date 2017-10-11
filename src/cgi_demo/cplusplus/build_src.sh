#!/bin/bash

rm build -rf
scons 
mkdir -p ../bin
cp build/* ../bin
rm build -rf
