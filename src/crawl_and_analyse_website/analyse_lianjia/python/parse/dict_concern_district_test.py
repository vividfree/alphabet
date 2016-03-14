#!/usr/bin/env python
# coding=utf-8

# Author: vividfree (vividfree@qq.com)
#  Date : 2016-03-13

import os
import sys
import unittest

import dict_concern_district

reload(sys)
sys.setdefaultencoding('utf-8')


class TestDictConcernDistrict(unittest.TestCase):
  def setUp(self):
    print >> sys.stderr, 'In TestDictConcernDistrict::test_init'

    dict_file = 'test_data/data/dict_concern_district'
    self.dict_ = dict_concern_district.DictConcernDistrict(dict_file)


  def test_is_concerned_district_id(self):
    print >> sys.stderr, 'In TestDictConcernDistrict::test_is_concerned_district_id'

    district_id = None
    res = self.dict_.is_concerned_district_id(district_id)
    self.assertFalse(res)

    district_id = 'zhichunlu1'
    res = self.dict_.is_concerned_district_id(district_id)
    self.assertFalse(res)

    district_id = 'zhichunlu'
    res = self.dict_.is_concerned_district_id(district_id)
    self.assertTrue(res)

    district_id = 'anzhen1'
    res = self.dict_.is_concerned_district_id(district_id)
    self.assertTrue(res)


  def test_get_district_hanzi_by_district_id(self):
    print >> sys.stderr, 'In TestDictConcernDistrict::test_get_district_hanzi_by_district_id'

    district_id = None
    res = self.dict_.get_district_hanzi_by_district_id(district_id)
    self.assertTrue(res is None)

    district_id = 'zhichunlu1'
    res = self.dict_.get_district_hanzi_by_district_id(district_id)
    self.assertTrue(res is None)

    district_id = 'zhichunlu'
    res = self.dict_.get_district_hanzi_by_district_id(district_id)
    self.assertTrue(res is not None)
    self.assertEqual('知春路', res)

    district_id = 'anzhen1'
    res = self.dict_.get_district_hanzi_by_district_id(district_id)
    self.assertTrue(res is not None)
    self.assertEqual('安贞', res)


  def test_get_url_of_all_district(self):
    print >> sys.stderr, 'In TestDictConcernDistrict::test_get_url_of_all_district'

    res = self.dict_.get_url_of_all_district()
    self.assertTrue(res is not None)
    self.assertEqual(10, len(res))
    self.assertTrue('http://bj.lianjia.com/fangjia/zhichunlu/' in res)
    self.assertTrue('http://bj.lianjia.com/fangjia/anzhen1/' in res)


if __name__ == '__main__':
  unittest.main()
