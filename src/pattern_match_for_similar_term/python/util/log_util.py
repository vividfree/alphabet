#!/usr/bin/env python

# log util
# Author: vividfree (vividfree@qq.com)
#  Date : 2017-08-18

import logging
import sys


def init_logger(logfile):
    default_logger = logging.getLogger()
    default_logger.setLevel(logging.INFO)

    log_format = "%(asctime)s\t[%(levelname)s]\t%(filename)s:%(lineno)d\t%(message)s"
    formatter = logging.Formatter(log_format)

    detail_handler = logging.StreamHandler(sys.stdout)
    detail_handler.setLevel(logging.DEBUG)
    detail_handler.setFormatter(formatter)
    default_logger.addHandler(detail_handler)

    err_handler = logging.FileHandler(logfile + '.err')
    err_handler.setLevel(logging.WARNING)
    err_handler.setFormatter(formatter)
    default_logger.addHandler(err_handler)

    return default_logger


def get_logger():
    return logging.getLogger()


if __name__ == '__main__':
    init_logger('./log.log_util')
    logger = get_logger()
    logger.info('info test')
    logger.error('error test')
