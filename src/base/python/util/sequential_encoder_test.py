#!/usr/bin/env python

# Author: vividfree (vividfree@qq.com)
#  Date : 2017-08-18

import unittest

from util import sequential_encoder
from util import log_util


class TestSequentialEncoder(unittest.TestCase):
    def setUp(self):
        self._logger = log_util.get_logger()
        self._reader = sequential_encoder.SequentialEncoder('test_data/test_data_for_sequential_encoder', '\t')

    def test_get_str_item_by_str_id(self):
        self._logger.info('In TestSequentialEncoder::test_get_str_item_by_str_id')

        self.assertEqual('def', self._reader.get_str_item_by_str_id('1'))
        self.assertEqual('opq', self._reader.get_str_item_by_str_id('2'))
        self.assertTrue(self._reader.get_str_item_by_str_id('3') is None)

    def test_get_int_id_by_str_item(self):
        self._logger.info('In TestSequentialEncoder::test_get_int_id_by_str_item')

        self.assertEqual(0, self._reader.get_int_id_by_str_item('abc'))
        self.assertEqual(2, self._reader.get_int_id_by_str_item('opq'))
        self.assertTrue(self._reader.get_int_id_by_str_item('fgh') is None)


if __name__ == '__main__':
    log_util.init_logger('./log.sequential_encoder')
    unittest.main()
