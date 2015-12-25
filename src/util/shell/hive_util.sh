#!/bin/bash -
#
# some hive related function for Shell
# Author: luowei (vividfree@qq.com)
# Date : 2015-12-25


function show_partition() {
  local input_database=$1
  local input_table=$2
  local sql="use ${input_database}; set hive.security.authorization.enabled=false; show partitions ${input_table}"
  echo ${sql}
  hive -e "${sql}"
}

function drop_hive_table() {
  local to_drop_table=$1
  local sql="drop table if exists ${to_drop_table}"
  echo ${sql}
  hive -e "${sql}"
}

function wait_table_partition_without_authorization() {
  local database=$1
  local table_name=$2 
  local table_partition=$3
  if [ $# -ge 4 ]
  then
    ((minute=$4*2))
  else
    # 15 hours
    minute=1800
  fi
  for ((i=0;i<=$minute;i=i+1))
  do
    cnt=`hive -e "set hive.security.authorization.enabled=false; use $database; show partitions $table_name" | grep $table_partition |wc -l`
    t=`date +"%F %T"`
    if [ "$cnt" = '1' ];
    then
      echo "$t Found partition $table_partition of table ${database}.$table_name ."
      return 0
    fi
    if [ $minute -eq 0 ]
    then
      break
    fi
    echo "$t Waiting partition $table_partition of table ${database}.$table_name to be ready ..."
    sleep 30 
  done
  echo "$t No partition $table_partition of table ${database}.$table_name found."
  return 1
}

function wait_table_partition_with_authorization() {
  local database=$1
  local table_name=$2 
  local table_partition=$3
  if [ $# -ge 4 ]
  then
    ((minute=$4*2))
  else
    # 15 hours
    minute=1800
  fi
  for ((i=0;i<=$minute;i=i+1))
  do
    cnt=`hive -e "use $database;show partitions $table_name" | grep $table_partition |wc -l`
    t=`date +"%F %T"`
    if [ "$cnt" = '1' ];
    then
      echo "$t Found partition $table_partition of table ${database}.$table_name ."
      return 0
    fi
    if [ $minute -eq 0 ]
    then
      break
    fi
    echo "$t Waiting partition $table_partition of table ${database}.$table_name to be ready ..."
    sleep 30 
  done
  echo "$t No partition $table_partition of table ${database}.$table_name found."
  return 1
}
