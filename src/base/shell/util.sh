#!/bin/bash -

# basic operation related function
# Author: vividfree (vividfree@qq.com)
#  Date : 2015-12-28

function check_job() {
  if [ $? -eq 0 ] 
  then
    echo "$@ success"
  else
    echo "$@ fail"
    exit 1
  fi  
}

function err() {
  echo "[$(date +'%Y-%m-%dT%H:%M:%S%z')]: $@" >&2
}
