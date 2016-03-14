#!/usr/bin/env python
# coding=utf-8

# Author: vividfree (vividfree@qq.com)
#  Date : 2016-03-13

from lxml import html

import chardet
import json
import re
import requests
import sys
import time
import urllib

import dict_city_level
import dict_concern_district
import xpath_util

reload(sys)
sys.setdefaultencoding("utf-8")

######  解析 城市级别 的房产情况  ######

class ParseLianjiaUtil(object):

  def __init__(self, dict_city_level_file, dict_concern_district_file):
    self.dict_city_level_ = \
        dict_city_level.DictCityLevel(dict_city_level_file)
    self.dict_concern_district_ = \
        dict_concern_district.DictConcernDistrict(dict_concern_district_file)


  def get_url_of_all_district(self):
    return self.dict_concern_district_.get_url_of_all_district()


  # 输入: city_id。示例: 'bj', 'sz'
  # 输出: city_detail 列表类型
  def parse_city_level_info(self, city_id):
    if not self.dict_city_level_.is_concerned_city_id(city_id):
      print >> sys.stderr, 'city_id [%s] is not concerned city_id ' \
                           'for parse_city_level_info()' \
                           %(city_id)
      return None

    url_prefix = 'http://'
    url_suffix = '.lianjia.com'
    url = '%s%s%s' %(url_prefix, city_id, url_suffix)
    page = requests.get(url)
    if 0 == len(page.content):
      print >> sys.stderr, 'url [%s] content is empty' %(url)
      return None

    page_content = page.content
    char_result = chardet.detect(page_content)
    print >> sys.stderr, 'url [%s] char_result [%s]' %(url, char_result)
    tree = html.fromstring(page_content)

    # step 1: 获取 city_id 对应的 city_pinyin 和 city_hanzi
    city_hanzi = self.dict_city_level_.get_city_hanzi_by_city_id(city_id)

    # step 2: 获取 city_id 对应的详细信息
    city_detail = []
    city_detail = self.parse_city_level_info_inner(tree)

    city_info = []
    for item in city_detail:
      city_info.append('%s\001%s' %(city_hanzi, item))
    return city_info


  # 输入: city_id。示例: 'bj', 'sz'
  # 输出: list<(district, url)>的列表
  def parse_city_sitemap(self, city_id):
    if not self.dict_city_level_.is_concerned_city_id(city_id):
      print >> sys.stderr, 'city_id [%s] is not concerned city_id ' \
                           'for parse_city_sitemap()' \
                           %(city_id)
      return None

    url_prefix = 'http://'
    url_suffix = '.lianjia.com/sitemap'
    url = '%s%s%s' %(url_prefix, city_id, url_suffix)
    page = requests.get(url)
    if 0 == len(page.content):
      print >> sys.stderr, 'url [%s] content is empty' %(url)
      return None

    page_content = page.content
    char_result = chardet.detect(page_content)
    print >> sys.stderr, 'url [%s] char_result [%s]' %(url, char_result)
    tree = html.fromstring(page_content)

    dict_district_and_url = self.parse_city_sitemap_inner(tree)
    return dict_district_and_url


  # 输入: url。示例: 'http://bj.lianjia.com/fangjia/haidian/'
  # 输出: district_detail 列表类型
  def parse_district_level_info(self, url):
    page = requests.get(url)
    if 0 == len(page.content):
      print >> sys.stderr, 'url [%s] content is empty' %(url)
      return None

    page_content = page.content
    char_result = chardet.detect(page_content)
    print >> sys.stderr, 'url [%s] char_result [%s]' %(url, char_result)
    tree = html.fromstring(page_content)

    district_info = self.parse_district_level_info_inner(tree)
    return district_info


  def parse_city_level_info_inner(self, tree):
    detail_list = []

    items = tree.xpath('//div[@class="data"]')
    for item in items:
      #print html.tostring(item)
      sub_items = item.xpath('.//div[@class="main"]/div[@class="title"]')
      for sub_item in sub_items:
        if sub_item.text is not None:
          detail_list.append(sub_item.text)

      key = ''
      val = ''
      sub_items = item.xpath('.//div[@class="main"]//div[@class="deal-price"]')
      for sub_item in sub_items:
        #print html.tostring(sub_item)
        subsub_items = sub_item.xpath('.//label')
        for subsub_item in subsub_items:
          if subsub_item.text is not None:
            val = subsub_item.text.strip()

        subsub_items = sub_item.xpath('.//p')
        for subsub_item in subsub_items:
          if subsub_item.text is not None:
            key = subsub_item.text.strip()

        detail_list.append('%s\002%s' %(key, val))

      key = ''
      val = ''
      sub_items = item.xpath('.//div[@class="main"]//div[@class="listing-price"]')
      for sub_item in sub_items:
        #print html.tostring(sub_item)
        subsub_items = sub_item.xpath('.//label')
        for subsub_item in subsub_items:
          if subsub_item.text is not None:
            val = subsub_item.text.strip()

        subsub_items = sub_item.xpath('.//p')
        for subsub_item in subsub_items:
          if subsub_item.text is not None:
            key = subsub_item.text.strip()

        detail_list.append('%s\002%s' %(key, val))

      key = ''
      val = ''
      sub_items = item.xpath('.//ul/li//a')
      for sub_item in sub_items:
        #print html.tostring(sub_item)
        subsub_items = sub_item.xpath('.//label')
        for subsub_item in subsub_items:
          if subsub_item.text is not None:
            val = subsub_item.text.strip()

        subsub_items = sub_item.xpath('.//p')
        for subsub_item in subsub_items:
          if subsub_item.text is not None:
            key = subsub_item.text.strip()

        detail_list.append('%s\002%s' %(key, val))

    return detail_list


  def parse_city_sitemap_inner(self, tree):
    dict_district_and_url = {}

    items = tree.xpath('//div/div[@class="div_con"][2]/ul/li')
    for item in items:
      #print html.tostring(item)
      cur_district = ''
      sub_items = item.xpath('./a[1]')
      for sub_item in sub_items:
        #print html.tostring(sub_item)
        district_name, district_url = \
            xpath_util.parse_anchor_and_superlink(sub_item)

        cur_district = '%s\002%s' %(district_name, district_url)
        if district_name not in dict_district_and_url:
          dict_district_and_url[cur_district] = []

      sub_items = item.xpath('./dl[@class="list"]/dd/a')
      for sub_item in sub_items:
        #print html.tostring(sub_item)
        sub_district_name, sub_district_url = \
            xpath_util.parse_anchor_and_superlink(sub_item)

        sub_district_name = sub_district_name.encode('utf8')
        to_append_item = '%s\002%s' %(sub_district_name, sub_district_url)
        # print >> sys.stderr, to_append_item
        if district_name not in dict_district_and_url:
          dict_district_and_url[cur_district].append(to_append_item)

    '''
    for key ,val in dict_district_and_url.iteritems():
      print >> sys.stderr, '[%s]' %(key)
      for item in val:
        print >> sys.stderr, '    [%s]' %(item)
    '''

    return dict_district_and_url


  def parse_district_level_info_inner(self, tree):
    detail_list = []

    district_name = ''
    items = tree.xpath('//div[@class="view-con"]')
    for item in items:
      #print html.tostring(item)
      sub_items = item.xpath('./h1')
      for sub_item in sub_items:
        #print html.tostring(sub_item)
        if sub_item.text is not None:
          district_name = sub_item.text

      key = ''
      val = ''
      sub_items = item.xpath('./div[@class="semid"]/div[@class="middle"]/span[1]')
      for sub_item in sub_items:
        #print html.tostring(sub_item)
        if sub_item.text is not None:
          key = sub_item.text
      sub_items = item.xpath('./div[@class="semid"]/div[@class="last"]/span[1]')
      for sub_item in sub_items:
        #print html.tostring(sub_item)
        if sub_item.text is not None:
          val = '%s元/平米' %(sub_item.text)
      detail_list.append('%s\002%s' %(key, val))

      key = ''
      val = ''
      sub_items = item.xpath('./div[@class="semid"]/div[@class="middle"]/span[2]')
      for sub_item in sub_items:
        #print html.tostring(sub_item)
        if sub_item.text is not None:
          key = sub_item.text
        subsub_items = sub_item.xpath('./span')
        for subsub_item in subsub_items:
          #print html.tostring(sub_item)
          if subsub_item.text is not None:
            val = subsub_item.text
      detail_list.append('%s\002%s' %(key, val))

      key = ''
      val = ''
      sub_items = item.xpath('./div[@class="semid"]/div[@class="middle"]/span[3]')
      for sub_item in sub_items:
        #print html.tostring(sub_item)
        if sub_item.text is not None:
          key = sub_item.text
        subsub_items = sub_item.xpath('./span')
        for subsub_item in subsub_items:
          #print html.tostring(sub_item)
          if subsub_item.text is not None:
            val = subsub_item.text
      detail_list.append('%s\002%s' %(key, val))

      info = ''
      sub_items = item.xpath('./div[@class="semid"]//div[@class="nearday"]/p/a')
      for sub_item in sub_items:
        #print html.tostring(sub_item)
        if sub_item.text is not None:
          info = sub_item.text
        detail_list.append('%s' %(info))

    items = tree.xpath('//div[@class="bottom"]/div[@class="four fl"]')
    for item in items:
      #print html.tostring(item)
      key = ''
      val = ''
      sub_items = item.xpath('./p')
      for sub_item in sub_items:
        #print html.tostring(sub_item)
        if sub_item.text is not None:
          key = sub_item.text
      sub_items = item.xpath('./p/span')
      for sub_item in sub_items:
        #print html.tostring(sub_item)
        if sub_item.text is not None:
          key += sub_item.text
      sub_items = item.xpath('./span')
      for sub_item in sub_items:
        #print html.tostring(sub_item)
        if sub_item.text is not None:
          val = sub_item.text
      detail_list.append('%s\002%s' %(key, val))

    detail_list = ['%s\001%s' %(district_name, item) for item in detail_list]
    #print >> sys.stderr, 'district_detail [%s]' %('\001'.join(detail_list))
    return detail_list
