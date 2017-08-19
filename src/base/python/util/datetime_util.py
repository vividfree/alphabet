# datetime util
# Author: vividfree (vividfree@qq.com)
#  Date : 2017-08-18

from datetime import datetime
from datetime import timedelta


def get_date_list_from_beg_to_end(str_beg_date, str_end_date, input_date_format, output_date_format):
    """
    return list from str_beg_date to str_end_date, including str_beg_date and str_end_date
    """
    assert str_beg_date <= str_end_date, 'str_beg_date [%s] should not be larger than str_end_date [%s]' \
                                         % (str_beg_date, str_end_date)
    date_list = list()
    cur_date = datetime.strptime(str_beg_date, input_date_format)
    str_cur_date = cur_date.strftime(output_date_format)
    str_end_date = transfer_date_format(str_end_date, input_date_format, output_date_format)
    while str_cur_date <= str_end_date:
        date_list.append(str_cur_date)
        next_date = cur_date + timedelta(1)
        str_cur_date = next_date.strftime(output_date_format)
        cur_date = next_date
    return date_list


def get_date_list_by_day_span_forward(str_beg_date, int_day_span, input_date_format, output_date_format):
    assert int_day_span > 0, 'int_day_span [%d] should not be lower than 0' % int_day_span
    date_list = list()
    cur_date = datetime.strptime(str_beg_date, input_date_format)
    for i in xrange(0, int_day_span):
        target_date = cur_date + timedelta(i)
        date_list.append(target_date.strftime(output_date_format))
    return date_list


def get_date_list_by_day_span_backward(str_beg_date, int_day_span, input_date_format, output_date_format):
    assert int_day_span >= 0, 'int_day_span [%d] should not be lower than 0' % int_day_span
    date_list = list()
    cur_date = datetime.strptime(str_beg_date, input_date_format)
    for i in xrange(0, int_day_span):
        target_date = cur_date - timedelta(i)
        date_list.append(target_date.strftime(output_date_format))
    return date_list


def get_relative_date(str_input_date, int_relative_days, input_date_format, output_date_format):
    if 0 == int_relative_days:
        if input_date_format == output_date_format:
            return str_input_date
        else:
            return transfer_date_format(str_input_date, input_date_format, output_date_format)

    tmp_date = datetime.strptime(str_input_date, input_date_format)
    result_date = tmp_date + timedelta(days=int_relative_days)
    return result_date.strftime(output_date_format)


def transfer_date_format(str_input_date, input_date_format, output_date_format):
    return datetime.strptime(str_input_date, input_date_format).strftime(output_date_format)
