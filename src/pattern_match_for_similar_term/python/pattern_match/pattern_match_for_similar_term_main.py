#!/usr/bin/env python
# -*-coding:utf-8-*-

# Author: vividfree (vividfree@qq.com)
#  Date : 2017-08-18

import os
import sys

from pattern_match import pattern_match_for_similar_term
from util import log_util
from util import project_path_getter


def run_job(data_file):
    pattern_match_file = os.path.join(project_path_getter.ProjectPathGetter().data_root(),
                                      'pattern_match_for_similar_term')
    print >> sys.stderr, 'pattern_match_file [%s]' % pattern_match_file
    matcher = pattern_match_for_similar_term.PatternMatchForSimilarTerm(pattern_match_file)

    count = 0
    for line in open(data_file):
        count += 1
        if count % 10000 == 0:
            print >> sys.stderr, 'deal with %d lines' % count

        line = line.strip().decode('utf-8')
        if not line:
            continue
        match_info = matcher.apply(line)
        my_print(line, match_info)


def my_print(input_str, match_info):
    if match_info:
        left_term, right_term, match_pattern_list = match_info
        print '%s\001%s\001%s\001%s' % (left_term.encode('utf-8'), right_term.encode('utf-8'),
                                        input_str.encode('utf-8'), ','.join(match_pattern_list))
    else:
        print 'NOT MATCH ANYTHING for input_str %s' % input_str.encode('utf-8')


if __name__ == '__main__':
    if 2 != len(sys.argv):
        print >> sys.stderr, 'Usage: %s data_file' % sys.argv[0]
        exit(9)
    main_data_file = sys.argv[1]

    log_util.init_logger('./log.pattern_match_for_similar_term_main')
    run_job(main_data_file)
