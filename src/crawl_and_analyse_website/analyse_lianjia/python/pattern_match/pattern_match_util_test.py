#!/usr/bin/env python
# coding=utf-8

# Author: vividfree (vividfree@qq.com)
#  Date : 2016-01-29

import os
import sys
import unittest

import pattern_match_util

reload(sys)
sys.setdefaultencoding('utf-8')


class TestStringUtil(unittest.TestCase):
  def test_re_match(self):
    print >> sys.stderr, 'In TestStringUtil::test_re_match'

    output_dict = {}
    pattern = 'http://www.autohome.com.cn/(?P<series_id>\d+?)/'
    input_url = 'http://www.autohome.com.cn/2731/#levelsource=000000000_0&pvareaid=101594'
    output_dict = pattern_match_util.re_match(pattern, input_url)
    self.assertEqual(1, len(output_dict))
    self.assertTrue('series_id' in output_dict)
    self.assertEqual('2731', output_dict['series_id'])

    pattern = 'http://car.autohome.com.cn/pic/series-s(?P<car_type_id>\d+?)/(?P<series_id>\d+?).html'
    input_url = 'http://car.autohome.com.cn/pic/series-s33300/2376.html#pvareaid=101594'
    output_dict = pattern_match_util.re_match(pattern, input_url)
    self.assertEqual(2, len(output_dict))
    self.assertTrue('series_id' in output_dict)
    self.assertEqual('2376', output_dict['series_id'])
    self.assertTrue('car_type_id' in output_dict)
    self.assertEqual('33300', output_dict['car_type_id'])
    self.assertTrue('car_type_id2' not in output_dict)

    input_url = 'http://car.autohome.com.cn/pi/series-s33300/2376.html#pvareaid=101594'
    output_dict = pattern_match_util.re_match(pattern, input_url)
    self.assertEqual(0, len(output_dict))
    self.assertTrue('car_type_id' not in output_dict)


if __name__ == '__main__':
  unittest.main()
