#!/usr/bin/env python
# coding=utf-8

# Author: vividfree (vividfree@qq.com)
#  Date : 2016-03-13

import parse_lianjia_util

import os
import sys
import unittest

reload(sys)
sys.setdefaultencoding('utf-8')

class TestParseLianjiaUtil(unittest.TestCase):

  def setUp(self):
    print >> sys.stderr, 'In TestParseLianjiaUtil::test_init'

    dict_city_level_file = 'test_data/data/dict_city_level'
    dict_concern_district_file = 'test_data/data/dict_concern_district'
    self.parser_ = \
        parse_lianjia_util.ParseLianjiaUtil(dict_city_level_file,
                                            dict_concern_district_file)


  def test_parse_city_level_info(self):
    print >> sys.stderr, 'In TestParseLianjiaUtil::test_parse_city_level_info'

    city_id = 'bj1'
    city_info = self.parser_.parse_city_level_info(city_id)
    self.assertTrue(city_info is None)

    city_id = 'bj'
    city_info = self.parser_.parse_city_level_info(city_id)
    self.assertTrue(city_info is not None)
    self.assertEqual(6, len(city_info))
    self.assertEqual('北京北京市2月二手房市场行情', city_info[0])
    self.assertEqual('北京二手房源全市均价(元/㎡)41867', city_info[1])
    self.assertEqual('北京二手房源挂牌均价(元/㎡)42686', city_info[2])
    self.assertEqual('北京昨日新增客房比4.1', city_info[3])
    self.assertEqual('北京昨日成交量(套)660', city_info[4])
    self.assertEqual('北京昨日房源带看量(次)39153', city_info[5])

    city_id = 'sz'
    city_info = self.parser_.parse_city_level_info(city_id)
    self.assertTrue(city_info is not None)
    self.assertEqual(6, len(city_info))
    self.assertEqual('深圳深圳市2月二手房市场行情', city_info[0])
    self.assertEqual('深圳二手房源全市均价(元/㎡)39679', city_info[1])
    self.assertEqual('深圳全市均价环比上月+2.61%', city_info[2])
    self.assertEqual('深圳昨日新增客房比1.5', city_info[3])
    self.assertEqual('深圳上月成交量(套)8846', city_info[4])
    self.assertEqual('深圳昨日房源带看量(次)4391', city_info[5])

    city_id = 'sh'
    city_info = self.parser_.parse_city_level_info(city_id)
    self.assertTrue(city_info is not None)
    self.assertEqual(6, len(city_info))
    self.assertEqual('上海上海市2月二手房市场行情', city_info[0])
    self.assertEqual('上海二手房源全市均价(元/㎡)35151', city_info[1])
    self.assertEqual('上海二手房源挂牌均价(元/㎡)42519', city_info[2])
    self.assertEqual('上海昨日新增客房比3.7', city_info[3])
    self.assertEqual('上海上月成交量(套)27972', city_info[4])
    self.assertEqual('上海昨日房源带看量(次)3186', city_info[5])


  def test_parse_city_sitemap(self):
    print >> sys.stderr, 'In TestParseLianjiaUtil::test_parse_city_sitemap'

    city_id = 'bj1'
    dict_district_and_url = self.parser_.parse_city_sitemap(city_id)
    self.assertTrue(dict_district_and_url is None)

    city_id = 'bj'
    dict_district_and_url = self.parser_.parse_city_sitemap(city_id)
    self.assertTrue(dict_district_and_url is not None)


  def test_parse_district_level_info(self):
    print >> sys.stderr, 'In TestParseLianjiaUtil::test_parse_district_level_info'

    url = 'http://bj.lianjia.com/fangjia/haidian/'
    district_info = self.parser_.parse_district_level_info(url)
    self.assertTrue(district_info is not None)

    url = 'http://bj.lianjia.com/fangjia/zhichunlu/'
    district_info = self.parser_.parse_district_level_info(url)
    self.assertTrue(district_info is not None)


if __name__ == '__main__':
  unittest.main()
