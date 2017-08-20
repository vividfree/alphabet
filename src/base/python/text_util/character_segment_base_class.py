# Author: vividfree (vividfree@qq.com)
#  Date : 2017-08-18
#   NOTE  : The input parameters of the functions within CharacterSegmentBaseClass
#           need to be string encoding with Unicode, so you should use str.decode(...)
#           first before invoking these functions.

from abc import ABCMeta, abstractmethod


class CharacterSegmentBaseClass(object):
    __metaclass__ = ABCMeta

    @abstractmethod
    def __init__(self):
        pass

    @abstractmethod
    def normalize_2_list(self, ustring):
        """
        :param ustring: input string encoding with Unicode
        :return: normalized string encoding with Unicode (type list)
        """
        pass

    @abstractmethod
    def normalize_2_ustring(self, ustring):
        """
        :param ustring: input string encoding with Unicode
        :return: normalized string encoding with Unicode (type ustring)
        """
        pass
