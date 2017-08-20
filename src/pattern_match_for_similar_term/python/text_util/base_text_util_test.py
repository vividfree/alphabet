#!/usr/bin/env python
# -*-coding:utf-8-*-

# Author: vividfree (vividfree@qq.com)
#  Date : 2017-08-18

import unittest

from text_util.base_text_util import BaseTextUtil
from util import log_util


class TestBaseTextUtil(unittest.TestCase):
    def setUp(self):
        self.logger_ = log_util.get_logger()

    def test_has_alphabet(self):
        self.logger_.info('In TestBaseTextUtil::test_has_alphabet')

        input_str = u'abc'
        self.assertTrue(BaseTextUtil.has_alphabet(input_str))

        input_str = u'123'
        self.assertFalse(BaseTextUtil.has_alphabet(input_str))

    def test_has_chinese(self):
        self.logger_.info('In TestBaseTextUtil::test_has_chinese')

        input_str = u'abc'
        self.assertFalse(BaseTextUtil.has_chinese(input_str))

        input_str = u'手机'
        self.assertTrue(BaseTextUtil.has_chinese(input_str))

        input_str = u'涓夋槦A9100'
        self.assertTrue(BaseTextUtil.has_chinese(input_str))

    def test_string_quanjiao_2_banjiao(self):
        self.logger_.info('In TestBaseTextUtil::test_string_quanjiao_2_banjiao')

        input_str = u'abc'
        ret_val = BaseTextUtil.string_quanjiao_2_banjiao(input_str)
        self.assertEqual(input_str, ret_val)

        input_str = u'手机'
        ret_val = BaseTextUtil.string_quanjiao_2_banjiao(input_str)
        self.assertEqual(input_str, ret_val)

        input_str = u'手机。'
        ret_val = BaseTextUtil.string_quanjiao_2_banjiao(input_str)
        self.assertEqual(input_str, ret_val)

        input_str = u'手机ａｂｃｄ．　ｈｅｌｌｏ足球'
        ret_val = BaseTextUtil.string_quanjiao_2_banjiao(input_str)
        self.assertEqual(u'手机abcd. hello足球', ret_val)

        input_str = u'“”“”手机ａｂｃｄ．　ｈｅｌｌｏ足球'
        ret_val = BaseTextUtil.string_quanjiao_2_banjiao(input_str)
        self.assertEqual(u'“”“”手机abcd. hello足球', ret_val)

    def test_delete_sys_chars(self):
        self.logger_.info('In TestBaseTextUtil::test_delete_sys_chars')

        input_str = u'ab\001cd\002ef\003g\004h\005i\tj'
        ret_val = BaseTextUtil.delete_sys_chars(input_str)
        self.assertEqual(u'ab cd ef g h i j', ret_val)

    def test_normalize(self):
        self.logger_.info('In TestBaseTextUtil::test_normalize')

        input_str = u'手机\001ａｂ\002ｃｄ\003．\004　\005ｈｅｌｌｏ\t足球'
        ret_val = BaseTextUtil.normalize(input_str)
        self.assertEqual(u'手机 ab cd .   hello 足球', ret_val)

if __name__ == '__main__':
    log_util.init_logger('./log.base_text_util')
    unittest.main()
