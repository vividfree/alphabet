#!/usr/bin/env python
# -*-coding:utf-8-*-

# Author: vividfree (vividfree@qq.com)
#  Date : 2017-08-18

import os
import sys
import unittest

from pattern_match import pattern_match_for_similar_term
from util import project_path_getter


class TestPatternMatch(unittest.TestCase):
    def setUp(self):
        print >> sys.stderr, 'In TestPatternMatch::test_init'

        pattern_match_file = os.path.join(project_path_getter.ProjectPathGetter().test_data_root(),
                                          'pattern_match_for_similar_term')
        print >> sys.stderr, 'pattern_match_file [%s]' % pattern_match_file
        self.matcher = pattern_match_for_similar_term.PatternMatchForSimilarTerm(pattern_match_file)

    def test_apply(self):
        print >> sys.stderr, 'In TestUrlPatternMatch::test_apply'

        input_str_list = list()
        input_str_list.append(u'苹果与小米对比')
        input_str_list.append(u'iphone与小米的对比')
        input_str_list.append(u'oppo和vivo对比')
        input_str_list.append(u'oppo r9和vivo的区别')
        input_str_list.append(u'我和我的小伙伴')
        input_str_list.append(u'喜洋洋与大灰狼之我爱灰太狼')
        input_str_list.append(u'喜洋洋与大灰狼间我爱灰太狼')
        input_str_list.append(u'喜洋洋和大灰狼之间我爱灰太狼')
        input_str_list.append(u'喜洋洋|大灰狼之间我爱灰太狼')
        input_str_list.append(u'喜洋洋与或大灰狼之间我爱灰太狼')
        input_str_list.append(u'喜洋洋与大灰狼有什么')
        input_str_list.append(u'喜洋洋与大灰狼有么')
        input_str_list.append(u'对比oppo和vivo P')
        input_str_list.append(u'比oppo和vivo P')
        input_str_list.append(u'切尔西vs曼城')

        for input_str in input_str_list:
            match_info = self.matcher.apply(input_str)
            TestPatternMatch._my_print(input_str, match_info)

    @staticmethod
    def _my_print(input_str, match_info):
        print '\ninput_str [%s]' % input_str.encode('utf-8')
        if match_info:
            left_term, right_term, match_pattern_list = match_info
            print '  %s\n  %s\n  %s' % (left_term.encode('utf-8'), right_term.encode('utf-8'),
                                        '\n  '.join(match_pattern_list))
        else:
            print '  NOT MATCH ANYTHING'


if __name__ == '__main__':
    unittest.main()
