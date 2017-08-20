# -*-coding:utf-8-*-

# Author: vividfree (vividfree@qq.com)
#  Date : 2017-08-18
#   NOTE  : pattern match for similar term
#           1. first match L1_pattern, then L2_pattern, L3_pattern...
#         : 2. The input parameters of the functions within PatternMatchForSimilarTerm
#              need to be string encoding with Unicode, so you should use str.decode(...)
#              first before invoking these functions.

import ConfigParser
import sys

from text_util import base_text_util
from text_util import pattern_match_util


class PatternMatchForSimilarTerm(object):
    def __init__(self, pattern_match_file):
        self.pattern_match_conf = ConfigParser.ConfigParser()
        self.pattern_match_conf.read(pattern_match_file)

        section_name = 'DEFAULT'
        self.num_of_level = self.pattern_match_conf.getint(section_name, 'num_of_level')

        self.match_section_sorted_dict = dict()
        for x in xrange(self.num_of_level):
            section_name = "L%d_pattern" % (x + 1)
            assert section_name in self.pattern_match_conf.sections()
            num_of_pattern = self.pattern_match_conf.getint(section_name, 'num_of_pattern')
            pattern_list = list()
            for index in xrange(0, num_of_pattern):
                option = 'pattern%d' % (index + 1)
                assert option in self.pattern_match_conf.options(section_name)
                pattern_list.append(self.pattern_match_conf.get(section_name, option).decode('utf-8'))
            self.match_section_sorted_dict[section_name] = pattern_list

        self._print_members()

    def _print_members(self):
        print >> sys.stderr, 'num_of_level [ %d ]' % self.num_of_level
        print >> sys.stderr, 'match_section_sorted_dict'
        for key, pattern_list in self.match_section_sorted_dict.iteritems():
            print >> sys.stderr, '  [ %s ] num [ %d ]' % (key, len(pattern_list))
            index = 1
            for pattern in pattern_list:
                print >> sys.stderr, '    %d: %s' % (index, pattern.encode('utf-8'))
                index += 1
        sys.stderr.flush()

    def apply(self, input_str):
        """ get similar term pair from input_str

        NOTE: return None if it cannot extract similar term from input_str

        Args:
          input_str: unicode string
        Returns:
          left_term: unicode string
          right_term: unicode string
          match_list: utf-8 string
        """
        input_str = input_str.strip()
        left_term, right_term, match_pattern_list = self._match(input_str)

        if not left_term or not right_term:
            return None
        if self._whether_is_bad_case(left_term, right_term, input_str):
            return None

        left_term, right_term = self._postdeal(left_term, right_term, input_str)

        return left_term, right_term, match_pattern_list

    def _match(self, input_str):
        match_dict = dict()
        match_pattern_list = list()
        max_match_num = 0

        for key, pattern_list in self.match_section_sorted_dict.iteritems():
            for pattern in pattern_list:
                dict_result = pattern_match_util.re_match(pattern, input_str)
                if not dict_result:
                    continue
                len_dict_result = len(dict_result)
                match_pattern_list.append('%s:%d:%s' % (key, len_dict_result, pattern.encode('utf-8')))
                if len_dict_result > max_match_num:
                    match_dict.clear()
                    match_dict = dict_result
                    max_match_num = len_dict_result
            if max_match_num > 0:
                break

        left_key_in_dict = 'left_term'
        right_key_in_dict = 'right_term'
        left_term = None
        right_term = None
        if left_key_in_dict in match_dict and right_key_in_dict in match_dict:
            if match_dict[left_key_in_dict] and match_dict[right_key_in_dict]:
                tmp_left_term = match_dict[left_key_in_dict].strip()
                tmp_right_term = match_dict[right_key_in_dict].strip()
                if tmp_left_term and tmp_right_term and tmp_left_term != tmp_right_term:
                    left_term = tmp_left_term
                    right_term = tmp_right_term
        return left_term, right_term, match_pattern_list

    @staticmethod
    def _whether_is_bad_case(left_term, right_term, input_str):
        # case 1
        if PatternMatchForSimilarTerm._is_short_term(left_term) or \
                PatternMatchForSimilarTerm._is_short_term(right_term):
            return True

        # case 2
        if PatternMatchForSimilarTerm._is_long_term(left_term) or \
                PatternMatchForSimilarTerm._is_long_term(right_term):
            return True

        # case 3
        length_ratio = 3
        if len(left_term) / len(right_term) > length_ratio or \
                len(right_term) / len(left_term) > length_ratio:
            return True

        # case 4
        if -1 != input_str.find(u"共和国") and left_term.endswith(u"共") and right_term.startswith(u"国"):
            return True

        # case 5
        if -1 != left_term.find(u'谁') or -1 != right_term.find(u'谁'):
            return True

        # case 6:
        if -1 != left_term.find(u',') or -1 != right_term.find(u','):
            return True

        # case 7:
        if -1 != left_term.find(u'、') or -1 != right_term.find(u'、'):
            return True

        # case 8:
        if -1 != left_term.find(u'我') or -1 != right_term.find(u'我'):
            return True

        # case 9:
        if -1 != left_term.find(u'某') or -1 != right_term.find(u'某'):
            return True

        # case 10:
        if -1 != left_term.find(u'什么') or -1 != right_term.find(u'什么'):
            return True

        # case 11:
        if -1 != left_term.find(u'不') or -1 != right_term.find(u'不'):
            return True

        return False

    @staticmethod
    def _is_short_term(term):
        if base_text_util.BaseTextUtil.has_chinese(term):
            if len(term) < 2:
                return True
        elif len(term) < 3:
            return True
        return False

    @staticmethod
    def _is_long_term(term):
        if len(term) > 8:
            return True
        return False

    @staticmethod
    def _postdeal(left_term, right_term, input_str):
        # case 1
        index = right_term.find(u"谁")
        if -1 != index and 0 != index:
            right_term = right_term[0:index]

        return left_term, right_term
