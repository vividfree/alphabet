#!/usr/bin/env python
# -*-coding:utf-8-*-

# Author: vividfree (vividfree@qq.com)
#  Date : 2017-08-18

import unittest

from text_util.character_segment_strategy_v1 import CharacterSegmentStrategyV1
from util import log_util


class TestCharacterSegmentStrategyV1(unittest.TestCase):
    def setUp(self):
        self._logger = log_util.get_logger()
        self._strategy = CharacterSegmentStrategyV1()

    def test_normalize_2_ustring(self):
        self._logger.info('In TestCharacterSegmentStrategyV1::test_normalize_2_ustring')

        str1 = u',abc.com.中国.'
        ret_val = self._strategy.normalize_2_ustring(str1)
        self.assertEqual(u'abc.com. 中 国', ret_val)

        str1 = u'.abc.com和abc.'
        ret_val = self._strategy.normalize_2_ustring(str1)
        self.assertEqual(u'abc.com 和 abc.', ret_val)

        str1 = u'.abc.com.和abc.,qihoo360'
        ret_val = self._strategy.normalize_2_ustring(str1)
        self.assertEqual(u'abc.com. 和 abc. qihoo360', ret_val)

        str1 = u'手机  http://abc.com  足球  hao.360.cn  hao123恒大'
        ret_val = self._strategy.normalize_2_ustring(str1)
        self.assertEqual(u'手 机 http://abc.com 足 球 hao.360.cn hao123 恒 大',
                         ret_val)

        str1 = u'手机  ＨＴＴＰ：／／ａｂｃ．ｃｏｍ  足球\t\001  ｈａｏ．３６０．ｃｎ\002  hao123\003恒大'
        ret_val = self._strategy.normalize_2_ustring(str1)
        self.assertEqual(u'手 机 http://abc.com 足 球 hao.360.cn hao123 恒 大',
                         ret_val)


if __name__ == '__main__':
    log_util.init_logger('./log.character_segment_strategy_v1')
    unittest.main()
