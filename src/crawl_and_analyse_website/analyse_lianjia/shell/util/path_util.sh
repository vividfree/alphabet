#!/bin/bash -

###### local related function ######

function mkdir_if_not_exist() {
  local_path=$1
  if [ ! -d ${local_path} ]; then
    mkdir -p ${local_path}
  fi
}

function mkdir_if_exist_and_del() {
  local_path=$1
  if [ -d ${local_path} ]; then
    echo "${local_path} exists, and will be delete"
    rm -rf ${local_path}
  fi
  mkdir -p ${local_path}
}

function del_if_exist() {
  local_path=$1
  if [ -d ${local_path} ]; then
    echo "${local_path} exists, and will be delete"
    rm -rf ${local_path}
  fi
}


######  hdfs related function  ######

function hdfs_mkdir_if_not_exist() {
  hdfs_path=$1
  hadoop fs -test -d ${hdfs_path}
  if [ $? -ne 0 ];then
    hadoop fs -mkdir ${hdfs_path}
  fi
}

function hdfs_mkdir_if_exist_and_del() {
  hdfs_path=$1
  hadoop fs -test -d ${hdfs_path}
  if [ $? -eq 0 ];then
    hadoop fs -rmr ${hdfs_path}
  fi
  hadoop fs -mkdir ${hdfs_path}
}

function hdfs_del_if_exist() {
  hdfs_path=$1
  hadoop fs -test -d ${hdfs_path}
  if [ $? -eq 0 ];then
    hadoop fs -rmr ${hdfs_path}
  fi
}
