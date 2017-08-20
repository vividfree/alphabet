# coding=utf-8

# sequential encoder
# Author: vividfree (vividfree@qq.com)
#  Date : 2017-08-18
#  NOTE : use delimiter to split line, then use field 0 to be concerned content

from util import log_util


class SequentialEncoder(object):
    def __init__(self, filename, delimiter):
        self._logger = log_util.get_logger()
        self._logger.info('data_file [%s]' % filename)
        self._logger.info('delimiter [%s]' % delimiter)

        self.int_id_2_str_item_dict = dict()
        self.str_item_2_int_id_dict = dict()

        index_id = 0
        fin = open(filename)
        for line in fin:
            fields = line.strip().split(delimiter)
            if not fields:
                continue
            content = fields[0]
            if content not in self.str_item_2_int_id_dict:
                self.str_item_2_int_id_dict[content] = index_id
                self.int_id_2_str_item_dict[index_id] = content
                index_id += 1
        fin.close()

    def get_str_item_by_str_id(self, str_id):
        int_id = int(str_id)
        if int_id not in self.int_id_2_str_item_dict:
            return None
        return self.int_id_2_str_item_dict[int_id]

    def get_int_id_by_str_item(self, str_item):
        if str_item not in self.str_item_2_int_id_dict:
            return None
        return self.str_item_2_int_id_dict[str_item]
