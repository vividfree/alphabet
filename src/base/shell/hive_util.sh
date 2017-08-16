#!/bin/bash -

# hive operation related function
# Author: vividfree (vividfree@qq.com)
#  Date : 2015-12-28

function drop_table () {
  table_name=$1
  sql="drop table if exists ${table_name}"
  echo ${sql}
  hive -e "${sql}"
}

function check_partition () {
  database_name=$1
  table_name=$2
  sql="use ${database_name}; set hive.security.authorization.enabled=false; show partitions ${table_name}"
  echo ${sql}
  hive -e "${sql}"
}

function wait_table_partition_without_authorization() {
  local database_name=$1
  local table_name=$2
  local partition_name=$3
  if [ $# -ge 4 ]
  then
    ((minute=$4*2))
  else
    # 15 hours
    minute=1800
  fi
  for ((i=0;i<=$minute;i=i+1))
  do
    cnt=`hive -e "set hive.security.authorization.enabled=false; use ${database_name}; show partitions ${table_name}" | grep ${partition_name} |wc -l`
    t=`date +"%F %T"`
    if [ "$cnt" = '1' ];
    then
      echo "$t Found partition ${partition_name} of table ${database_name}.${table_name} ."
      return 0
    fi
    if [ $minute -eq 0 ]
    then
      break
    fi
    echo "$t Waiting partition ${partition_name} of table ${database_name}.${table_name} to be ready ..."
    sleep 30
  done
  echo "$t No partition ${partition_name} of table ${database_name}.${table_name} found."
  return 1
}

function wait_table_partition_with_authorization() {
  local database_name=$1
  local table_name=$2
  local partition_name=$3
  if [ $# -ge 4 ]
  then
    ((minute=$4*2))
  else
    # 15 hours
    minute=1800
  fi
  for ((i=0;i<=$minute;i=i+1))
  do
    cnt=`hive -e "use ${database_name};show partitions ${table_name}" | grep ${partition_name} |wc -l`
    t=`date +"%F %T"`
    if [ "$cnt" = '1' ];
    then
      echo "$t Found partition ${partition_name} of table ${database_name}.${table_name} ."
      return 0
    fi
    if [ $minute -eq 0 ]
    then
      break
    fi
    echo "$t Waiting partition ${partition_name} of table ${database_name}.${table_name} to be ready ..."
    sleep 30
  done
  echo "$t No partition ${partition_name} of table ${database_name}.${table_name} found."
  return 1
}
