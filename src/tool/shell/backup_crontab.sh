#!/usr/bin/env bash
BACK=~/backup_crontab

# init
if [ ! -e ${BACK} ]; then
  mkdir -p ${BACK}
fi

# backup
echo "${BACK}/info_crontab.`date +%Y-%m-%d-%H-%M-%S`.txt"
/usr/bin/crontab -l > ${BACK}/info_crontab.`date +%Y-%m-%d-%H-%M-%S`.txt

# clean
find ${BACK} -name "info_crontab*" -mtime +7 | xargs rm -f
