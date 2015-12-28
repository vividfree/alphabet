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
