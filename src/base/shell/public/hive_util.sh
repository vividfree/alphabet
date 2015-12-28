#!/bin/bash -

# hive operation related function
# Author: vividfree (vividfree@qq.com)
#  Date : 2015-12-28

function drop_table () {
  to_drop_table=$1
  sql="drop table if exists ${to_drop_table}"
  echo ${sql}
  hive -e "${sql}"
}

function check_partition () {
  input_database=$1
  input_table=$2
  sql="use ${input_database}; set hive.security.authorization.enabled=false; show partitions ${input_table}"
  echo ${sql}
  hive -e "${sql}"
}
