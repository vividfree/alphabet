#!/bin/bash -

# file operation related function
# Author: vividfree (vividfree@qq.com)
#  Date : 2015-12-28

function get_value_by_key_from_ini_file() {
  ini_file=$1
  section=$2
  key=$3
  _readIni=`awk -F '=' '/\['${section}'\]/{a=1}a==1&&$1~/'${key}'/{print $2;exit}' ${ini_file}`
  echo ${_readIni}
}
