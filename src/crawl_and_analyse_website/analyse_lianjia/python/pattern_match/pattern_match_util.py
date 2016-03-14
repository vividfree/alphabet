#!/usr/bin/env python
# coding=utf-8

# Author: vividfree (vividfree@qq.com)
#  Date : 2016-01-28

import os
import re
import sys

reload(sys)
sys.setdefaultencoding('utf-8')


def re_match(pattern, input_str):
  output_dict = {}
  match = re.match(pattern, input_str)
  if match:
    for k, v in match.groupdict().items():
      output_dict[k] = v
  return output_dict
