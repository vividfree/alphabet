#!/usr/bin/env python

# Author: vividfree (vividfree@qq.com)
#  Date : 2017-08-18

import unittest

from util import key_value_file_reader
from util import log_util


class TestKeyValueFileReader(unittest.TestCase):
    def setUp(self):
        self._logger = log_util.get_logger()
        self._reader = key_value_file_reader.KeyValueFileReader('test_data/test_data_for_key_value_file_reader', '\t')

    def test_get_value_by_key(self):
        self._logger.info('In TestKeyValueFileReader::test_get_value_by_key')

        self.assertEqual('b12', self._reader.get_value_by_key('abc'))
        self.assertEqual('d45', self._reader.get_value_by_key('def'))
        self.assertTrue(self._reader.get_value_by_key('fgh') is None)


if __name__ == '__main__':
    log_util.init_logger('./log.key_value_file_reader')
    unittest.main()
