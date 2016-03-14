#!/usr/bin/env python
# coding=utf-8

# Author: vividfree (vividfree@qq.com)
#  Date : 2016-03-13
# 词典格式: city_pinyin \001 city_hanzi \001 city_id_in_lianjia

import sys

reload(sys)
sys.setdefaultencoding("utf-8")

######  城市级别 的词典  ######

class DictCityLevel(object):

  def __init__(self, dict_file):
    # step 1: 加载词典 
    self.dict_data_ = self.read_dict_file(dict_file)

    # step 2: 打印成员变量信息
    self.print_member_variable(dict_file, self.dict_data_)


  def read_dict_file(self, dict_file):
    dict_data = {}
    for line in open(dict_file):
      line = line.strip()
      if 0 == len(line) or line.startswith('#'):
        continue
      fields = line.split('\001')
      if 3 != len(fields):
        print >> sys.stderr, 'fields num [%d] not 3 in line [%s]' \
                             %(len(fields), line)
        continue
      
      # fields 3项依次是 city_pinyin, city_hanzi, city_id_in_lianjia
      city_id = fields[2]
      if city_id not in dict_data:
        dict_data[city_id] = []
        dict_data[city_id].append(fields[0])
        dict_data[city_id].append(fields[1])
      else:
        print >> sys.stderr, 'city_id [%s] duplicate in dict' %(city_id)
        continue

    return dict_data


  def print_member_variable(self, dict_name, dict_data):
    print >> sys.stderr, '\ndict_name [%s]' %(dict_name)
    for key, val in dict_data.items():
      print >> sys.stderr, '  [%s]\t[%s]' %(key, '\001'.join(val))


  def is_concerned_city_id(self, city_id):
    return city_id in self.dict_data_


  def get_city_pinyin_by_city_id(self, city_id):
    if city_id not in self.dict_data_:
      return None
    return self.dict_data_[city_id][0]


  def get_city_hanzi_by_city_id(self, city_id):
    if city_id not in self.dict_data_:
      return None
    return self.dict_data_[city_id][1]
