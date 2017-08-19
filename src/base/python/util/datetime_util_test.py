#!/usr/bin/env python

# Author: vividfree (vividfree@qq.com)
#  Date : 2017-08-18

import unittest

from util import datetime_util
from util import log_util


class TestDatetimeUtil(unittest.TestCase):
    def setUp(self):
        self._logger = log_util.get_logger()

    def test_get_date_list_from_beg_to_end(self):
        self._logger.info('In TestDatetimeUtil::test_get_date_list_from_beg_to_end')

        str_beg_date = '2017-08-01'
        str_end_date = '2017-08-03'
        input_date_format = '%Y-%m-%d'
        output_date_format = '%Y%m%d'

        date_list = datetime_util.get_date_list_from_beg_to_end(
            str_beg_date,
            str_end_date,
            input_date_format,
            output_date_format)
        expected_date_list = ['20170801', '20170802', '20170803']
        self.assertEqual(3, len(date_list))
        self.assertEqual(expected_date_list[0], date_list[0])
        self.assertEqual(expected_date_list[1], date_list[1])
        self.assertEqual(expected_date_list[2], date_list[2])

    def test_get_date_list_by_day_span_forward(self):
        self._logger.info('In TestDatetimeUtil::test_get_date_list_by_day_span_forward')

        str_beg_date = '2017-08-01'
        int_day_span = 4
        input_date_format = '%Y-%m-%d'
        output_date_format = '%Y%m%d'

        date_list = datetime_util.get_date_list_by_day_span_forward(
            str_beg_date,
            int_day_span,
            input_date_format,
            output_date_format)
        expected_date_list = ['20170801', '20170802', '20170803', '20170804']
        self.assertEqual(4, len(date_list))
        self.assertEqual(expected_date_list[0], date_list[0])
        self.assertEqual(expected_date_list[1], date_list[1])
        self.assertEqual(expected_date_list[2], date_list[2])
        self.assertEqual(expected_date_list[3], date_list[3])

    def test_get_date_list_by_day_span_backward(self):
        self._logger.info('In TestDatetimeUtil::test_get_date_list_by_day_span_backward')

        str_beg_date = '2017-08-01'
        int_day_span = 5
        input_date_format = '%Y-%m-%d'
        output_date_format = '%Y%m%d'

        date_list = datetime_util.get_date_list_by_day_span_backward(
            str_beg_date,
            int_day_span,
            input_date_format,
            output_date_format)
        expected_date_list = ['20170801', '20170731', '20170730', '20170729', '20170728']
        self.assertEqual(5, len(date_list))
        self.assertEqual(expected_date_list[0], date_list[0])
        self.assertEqual(expected_date_list[1], date_list[1])
        self.assertEqual(expected_date_list[2], date_list[2])
        self.assertEqual(expected_date_list[3], date_list[3])
        self.assertEqual(expected_date_list[4], date_list[4])

    def test_get_relative_date(self):
        self._logger.info('In TestDatetimeUtil::test_get_relative_date')

        str_beg_date = '2017-08-01'
        int_relative_days = 6
        input_date_format = '%Y-%m-%d'
        output_date_format = '%Y%m%d'

        result_date = datetime_util.get_relative_date(
            str_beg_date,
            int_relative_days,
            input_date_format,
            output_date_format)
        self.assertEqual('20170807', result_date)

        int_relative_days = -4
        result_date = datetime_util.get_relative_date(
            str_beg_date,
            int_relative_days,
            input_date_format,
            output_date_format)
        self.assertEqual('20170728', result_date)

    def test_transfer_date_format(self):
        self._logger.info('In TestDatetimeUtil::test_transfer_date_format')

        str_beg_date = '2017-08-01'
        input_date_format = '%Y-%m-%d'
        output_date_format = '%Y%m%d'

        result_date = datetime_util.transfer_date_format(
            str_beg_date,
            input_date_format,
            output_date_format)
        self.assertEqual('20170801', result_date)


if __name__ == '__main__':
    log_util.init_logger('./log.datetime_util')
    unittest.main()
