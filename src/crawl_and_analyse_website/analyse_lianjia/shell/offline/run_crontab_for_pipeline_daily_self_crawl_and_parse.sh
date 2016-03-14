#!/bin/bash -

today=$(date +%Y%m%d)
echo "today: $today"

str_date=${today}
echo "str_date: $str_date"

sh pipeline_daily_self_crawl_and_parse.sh ${str_date}
