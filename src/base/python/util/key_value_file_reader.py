# coding=utf-8

# key value file reader
# Author: vividfree (vividfree@qq.com)
#  Date : 2017-08-18

from util import log_util


class KeyValueFileReader(object):
    def __init__(self, filename, delimiter):
        self._logger = log_util.get_logger()
        self._logger.info('filename [%s]' % filename)
        self._logger.info('delimiter [%s]' % delimiter)

        self._dict = dict()
        fin = open(filename)
        for line in fin:
            key, value = line.strip().split(delimiter, 1)
            if key not in self._dict:
                self._dict[key] = value
        fin.close()

    def get_value_by_key(self, key):
        if key not in self._dict:
            return None
        return self._dict[key]
