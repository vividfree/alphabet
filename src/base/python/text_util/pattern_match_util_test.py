#!/usr/bin/env python
# -*-coding:utf-8-*-

# Author: vividfree (vividfree@qq.com)
#  Date : 2017-08-18


import sys
import unittest

import pattern_match_util


class TestStringUtil(unittest.TestCase):
    def test_re_match(self):
        print >> sys.stderr, 'In TestStringUtil::test_re_match'

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

        pattern = 'http://www.autohome.com.cn/(?P<car_jibie>\w+?)/(' \
                  '?P<car_selection>.*-\d+-\d+-\d+-\d+-\d+-\d+-\d+-\d+?)/'
        input_url = 'http://www.autohome.com.cn/car/0_0-0.0_0.0-0-0-0-0-5-0-0-0/###'
        output_dict = pattern_match_util.re_match(pattern, input_url)
        self.assertEqual(2, len(output_dict))
        self.assertTrue('car_jibie' in output_dict)
        self.assertEqual('car', output_dict['car_jibie'])
        self.assertEqual('0_0-0.0_0.0-0-0-0-0-5-0-0-0', output_dict['car_selection'])

        input_url = 'http://www.autohome.com.cn/car/0_0-0.0_0.0-0-0-0-0-5-0-0-0d/###'
        output_dict = pattern_match_util.re_match(pattern, input_url)
        self.assertEqual(0, len(output_dict))

        input_url = 'http://www.autohome.com.cn/car/0_0-0.0_0.0-0-0-0-0-5-0-d0-0/###'
        output_dict = pattern_match_util.re_match(pattern, input_url)
        self.assertEqual(0, len(output_dict))

        input_url = 'http://www.autohome.com.cn/car/0-0-0-0-5-0-0-0/###'
        output_dict = pattern_match_util.re_match(pattern, input_url)
        self.assertEqual(0, len(output_dict))

        input_url = 'http://www.autohome.com.cn/car/-0-0-0-0-5-0-0-0/###'
        output_dict = pattern_match_util.re_match(pattern, input_url)
        self.assertEqual(2, len(output_dict))
        self.assertTrue('car_jibie' in output_dict)
        self.assertEqual('car', output_dict['car_jibie'])
        self.assertEqual('-0-0-0-0-5-0-0-0', output_dict['car_selection'])


if __name__ == '__main__':
  unittest.main()
