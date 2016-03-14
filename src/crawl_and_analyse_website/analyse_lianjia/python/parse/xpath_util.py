#!/usr/bin/env python
# coding=utf-8

# Author: vividfree (vividfree@qq.com)
#  Date : 2016-01-12

from lxml import html

import sys

reload(sys)
sys.setdefaultencoding("utf-8")

# 解析 锚文本 及其 超链接
def parse_anchor_and_superlink(input_html_item):
  if not isinstance(input_html_item, html.HtmlElement):
    print >> sys.stderr, 'input_html_item type [%s] ' \
                         'not lxml.html.HtmlElement' %(type(input_html_item))
    return None, None

  cur_str = input_html_item.text
  cur_urls = input_html_item.xpath('@href')
  if 1 != len(cur_urls):
    return None, None
  cur_url = cur_urls[0]
  return cur_str, cur_url
