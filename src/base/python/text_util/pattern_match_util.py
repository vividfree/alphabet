# Author: vividfree (vividfree@qq.com)
#  Date : 2017-08-18

import re


def re_match(pattern, input_str):
    output_dict = {}
    match = re.match(pattern, input_str)
    if match:
        for k, v in match.groupdict().items():
            output_dict[k] = v
    return output_dict
