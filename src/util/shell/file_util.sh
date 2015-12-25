#!/bin/bash -
#
# some file related function for Shell
# Author: luowei (vividfree@qq.com)
# Date : 2015-12-25


###########################################
# read item from ini
###########################################

function read_item_from_ini() {
  local ini_file=$1;
  local section=$2;
  local item=$3
  local item_value=`awk -F '=' '/\['${section}'\]/{a=1}a==1&&$1~/'${item}'/{print $2;exit}' ${ini_file}`
  echo ${item_value}
}
