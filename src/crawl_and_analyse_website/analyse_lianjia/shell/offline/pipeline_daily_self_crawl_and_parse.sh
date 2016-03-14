#!/bin/bash -

######  detect str_date  ######

if [[ 1 == $# ]]; then
  str_date=$1
else
  echo "Usage: $0 str_date"
  echo "system exit"
  exit 9
fi

echo 'str_date:'${str_date}

######  DO NOT Modify this section  ######

PROJECT_ROOT=$(dirname $(dirname $(dirname $(readlink -f $0))))
source ~/.bashrc
export PYTHONPATH=${PROJECT_ROOT}/python:$PYTHONPATH
source ${PROJECT_ROOT}/shell/util/file_util.sh
source ${PROJECT_ROOT}/shell/util/path_util.sh
source ${PROJECT_ROOT}/shell/util/util.sh

conf_path=${PROJECT_ROOT}/conf/pipeline_analyse_lianjia.ini

begin=$(date "+%Y-%m-%d %H:%M:%S")

######  main_autohome_daily_self_crawl_and_parse  ######

script_path=${PROJECT_ROOT}/python/parse
python ${script_path}/main_lianjia_daily_self_crawl_and_parse.py ${conf_path} ${str_date}
check_job ${PROJECT_ROOT} ${str_date} "main_lianjia_daily_self_crawl_and_parse.py"

echo

######  DO NOT Modify this section  ######

end=$(date "+%Y-%m-%d %H:%M:%S")
echo "[pipeline_daily_self_crawl_and_parse] begin at $begin, end at $end"
