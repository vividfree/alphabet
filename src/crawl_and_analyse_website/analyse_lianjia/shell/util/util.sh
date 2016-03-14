#!/bin/bash -

function check_job() {
  if [[ $? -eq 0 ]]; then
    str_status="SUCCESS"
  else
    str_status="FAILED"
  fi

  PROJECT_ROOT=$1
  str_date=$2
  job_name=$3
  echo 'check_job result: ' ${str_date} ${job_name} ${str_status}

  if [[ ${str_status} == "FAILED" ]]; then
    exit 1
  fi
}
