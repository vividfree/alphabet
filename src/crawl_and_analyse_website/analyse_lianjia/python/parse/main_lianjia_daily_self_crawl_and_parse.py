#!/usr/bin/env python
# coding=utf-8

# Author: vividfree (vividfree@qq.com)
#  Date : 2016-03-13

from util import file_system, project_dir_manager

import ConfigParser
import os
import shutil
import sys
import time

import dict_concern_district
import parse_lianjia_util

reload(sys)
sys.setdefaultencoding("utf-8")

def run(conf_file, str_date):
  conf = ConfigParser.ConfigParser()
  conf.read(conf_file)

  str_section_name = 'daily_self_crawl_and_parse'

  # step 1: 获取用于输入的dict文件
  local_dict_root = os.path.join(project_dir_manager.data_root(),
                                 conf.get(str_section_name, 'input_dict'))
  input_dict_city_level = \
      os.path.join(local_dict_root,
                   conf.get(str_section_name, 'input_dict_city_level'))
  input_dict_concern_district = \
      os.path.join(local_dict_root,
                   conf.get(str_section_name, 'input_dict_concern_district'))

  # step 2: 获取dict_path目录并建立本地目录
  dict_path_without_date = \
      conf.get(str_section_name, 'dict_path_lianjia')
  dict_path_with_date = \
      os.path.join(dict_path_without_date, str_date)

  local_output_dict_path = \
      os.path.join(project_dir_manager.data_root(),
                   dict_path_with_date)

  if os.path.exists(local_output_dict_path):
    print 'local_output_dict_path: [%s] exists' %(local_output_dict_path)
    shutil.rmtree(local_output_dict_path)
  os.makedirs(local_output_dict_path)

  # step 3: 获取输出文件名
  local_output_city_level_info = \
      os.path.join(local_output_dict_path,
                   conf.get(str_section_name, 'city_level_info'))
  local_output_district_level_info = \
      os.path.join(local_output_dict_path,
                   conf.get(str_section_name, 'district_level_info'))
  local_output_certain_district_level_info = \
      os.path.join(local_output_dict_path,
                   conf.get(str_section_name, 'certain_district_level_info'))

  # step 4: 计算并把内容输出到文件
  parse_lianjia(input_dict_city_level,
                input_dict_concern_district,
                local_output_city_level_info,
                local_output_district_level_info,
                local_output_certain_district_level_info)


def parse_lianjia(input_dict_city_level,
                  input_dict_concern_district,
                  output_city_level_info,
                  output_district_level_info,
                  output_certain_district_level_info):
  fout_city = open(output_city_level_info, 'w')
  fout_district = open(output_district_level_info, 'w')
  fout_certain_district = open(output_certain_district_level_info, 'w')

  parser = parse_lianjia_util.ParseLianjiaUtil(input_dict_city_level,
                                               input_dict_concern_district)

  city_id_list = ['bj', 'gz', 'sh', 'sz']

  for city_id in city_id_list:
    city_info = parser.parse_city_level_info(city_id)
    if city_info is None:
      continue
    for item in city_info:
      print >> fout_city, item
    print >> fout_city, '\n'

  fout_city.close()

  city_id_list = ['bj']

  for city_id in city_id_list:
    dict_district_and_url = parser.parse_city_sitemap(city_id)
    if dict_district_and_url is None:
      continue
    for district_info, url_list in dict_district_and_url.iteritems():
      print >> fout_district, '%s' %(district_info)
      fields = district_info.split('\002')
      if 2 != len(fields):
        print >> sys.stderr, 'fields num [%d] not 2 in district_info [%s]' \
                             %(len(fields), district_info)
        continue
      district_detail = parser.parse_district_level_info(fields[1])
      for item in district_detail:
        print >> fout_district, item
      print >> fout_district, '\n'

  fout_district.close()

  url_list = parser.get_url_of_all_district()
  for url in url_list:
    district_detail = parser.parse_district_level_info(url)
    if district_detail is None:
      continue
    for item in district_detail:
      print >> fout_certain_district, item
    print >> fout_certain_district, '\n'

  fout_certain_district.close()


if __name__ == '__main__':
  if 3 != len(sys.argv):
    print >> sys.stderr, 'Usage: %s conf_file str_date' %(sys.argv[0])
    exit(9)

  conf_file = sys.argv[1]
  str_date = sys.argv[2]

  run(conf_file, str_date)
