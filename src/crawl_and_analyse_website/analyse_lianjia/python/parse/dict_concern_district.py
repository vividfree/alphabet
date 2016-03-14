#!/usr/bin/env python
# coding=utf-8

# Author: vividfree (vividfree@qq.com)
#  Date : 2016-03-13
# 词典格式: district_id \001 district_hanzi \001 belong_district \001 city_id

import sys

reload(sys)
sys.setdefaultencoding("utf-8")

######  区域级别 的词典  ######

class DictConcernDistrict(object):

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
      if 4 != len(fields):
        print >> sys.stderr, 'fields num [%d] not 4 in line [%s]' \
                             %(len(fields), line)
        continue
      
      # fields 4项依次是 district_id, district_hanzi, belong_district, city_id
      district_id = fields[0]
      if district_id not in dict_data:
        dict_data[district_id] = []
        dict_data[district_id].append(fields[1])
        dict_data[district_id].append(fields[2])
        dict_data[district_id].append(fields[3])
      else:
        print >> sys.stderr, 'district_id [%s] duplicate in dict' %(district_id)
        continue

    return dict_data


  def print_member_variable(self, dict_name, dict_data):
    print >> sys.stderr, '\ndict_name [%s]' %(dict_name)
    for key, val in dict_data.items():
      print >> sys.stderr, '  [%s]\t[%s]' %(key, '\001'.join(val))


  def is_concerned_district_id(self, district_id):
    return district_id in self.dict_data_


  def get_district_hanzi_by_district_id(self, district_id):
    if district_id not in self.dict_data_:
      return None
    return self.dict_data_[district_id][0]


  def get_url_of_all_district(self):
    url_list = []
    for key, val in self.dict_data_.iteritems():
      url = 'http://%s.lianjia.com/fangjia/%s/' %(val[2], key)
      url_list.append(url)
    return url_list
