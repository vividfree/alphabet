#!/bin/bash -

# file operation related function
# Author: vividfree (vividfree@qq.com)
#  Date : 2015-12-28

function read_value_from_ini() {
  INIFILE=$1;
  SECTION=$2;
  ITEM=$3
  _readIni=`awk -F '=' '/\['$SECTION'\]/{a=1}a==1&&$1~/'$ITEM'/{print $2;exit}' $INIFILE`
  echo ${_readIni}
}
