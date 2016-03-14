#!/usr/bin/env python
# coding=utf-8

# Author: vividfree (vividfree@qq.com)
#  Date : 2016-03-13

import os
import sys
import unittest

import dict_city_level

reload(sys)
sys.setdefaultencoding('utf-8')


class TestDictCityLevel(unittest.TestCase):
  def setUp(self):
    print >> sys.stderr, 'In TestDictCityLevel::test_init'

    dict_file = 'test_data/data/dict_city_level'
    self.dict_ = dict_city_level.DictCityLevel(dict_file)


  def test_is_concerned_city_id(self):
    print >> sys.stderr, 'In TestDictCityLevel::test_is_concerned_city_id'

    city_id = None
    res = self.dict_.is_concerned_city_id(city_id)
    self.assertFalse(res)

    city_id = 'sz1'
    res = self.dict_.is_concerned_city_id(city_id)
    self.assertFalse(res)

    city_id = 'sz'
    res = self.dict_.is_concerned_city_id(city_id)
    self.assertTrue(res)

    city_id = 'bj'
    res = self.dict_.is_concerned_city_id(city_id)
    self.assertTrue(res)


  def test_get_city_pinyin_by_city_id(self):
    print >> sys.stderr, 'In TestDictCityLevel::test_get_city_pinyin_by_city_id'

    city_id = None
    res = self.dict_.get_city_pinyin_by_city_id(city_id)
    self.assertTrue(res is None)

    city_id = 'sz1'
    res = self.dict_.get_city_pinyin_by_city_id(city_id)
    self.assertTrue(res is None)

    city_id = 'sz'
    res = self.dict_.get_city_pinyin_by_city_id(city_id)
    self.assertTrue(res is not None)
    self.assertEqual('shenzhen', res)

    city_id = 'bj'
    res = self.dict_.get_city_pinyin_by_city_id(city_id)
    self.assertTrue(res is not None)
    self.assertEqual('beijing', res)


  def test_get_city_hanzi_by_city_id(self):
    print >> sys.stderr, 'In TestDictCityLevel::test_get_city_hanzi_by_city_id'

    city_id = None
    res = self.dict_.get_city_hanzi_by_city_id(city_id)
    self.assertTrue(res is None)

    city_id = 'sz1'
    res = self.dict_.get_city_hanzi_by_city_id(city_id)
    self.assertTrue(res is None)

    city_id = 'sz'
    res = self.dict_.get_city_hanzi_by_city_id(city_id)
    self.assertTrue(res is not None)
    self.assertEqual('深圳', res)

    city_id = 'bj'
    res = self.dict_.get_city_hanzi_by_city_id(city_id)
    self.assertTrue(res is not None)
    self.assertEqual('北京', res)


if __name__ == '__main__':
  unittest.main()
