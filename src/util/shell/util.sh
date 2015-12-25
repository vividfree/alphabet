#!/bin/bash -
#
# some basic function for Shell
# Author: luowei (vividfree@qq.com)
# Date : 2015-12-25


###########################################
# detect whether the last command returns 0
###########################################

function check_job() {
  if [ $? -eq 0 ] 
  then
    err "$@ success"
  else
    err "$@ failed"
    exit 1
  fi  
}

###########################################
# err function to stderr
###########################################

function err() {
  echo "[$(date +'%Y-%m-%dT%H:%M:%S%z')]: $@" >&2
}
