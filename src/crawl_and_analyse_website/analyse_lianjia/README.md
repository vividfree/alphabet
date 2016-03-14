# analyse_lianjia

## 项目简介

开发目的: 抓取和解析一些链家的网页，以辅助分析房地产行业的宏观情况

开发语言: Python, Shell, xpath(xpath对应的Python包为lxml)

## 项目目录的结构说明

项目包括如下几个子目录：

    - build.sh : 项目的打包脚本
    - conf     : 项目的配置文件
    - data     : 项目的数据文件
    - python   : 项目的 Python  相关源代码
    - shell    : 项目的 Shell   相关源代码

1. build.sh 是项目的打包脚本。一般情况下开发机与线上机器是不同的机器，打包脚本能方便项目部署。
2. 项目一般会包括多个模块，各个模块一般都需要准备单测文件，甚至是测试数据。模块的单测文件和单测所用的测试数据就放在对应的模块中，这样方便系统维护（比如回归测试）。

## 解析结果示例

示例位于 data/example_of_analyse_result/20160314 中

文件内容解释：

    - certain_district_level_info.txt : 特定区域的宏观房产信息（比如：北京的五道口、上地、中关村等）
    - city_level_info.txt             : 城市级别的宏观房产信息（比如：北京、上海、广州、深圳等）
    - district_level_info.txt         : 区级别的宏观房产信息（比如：北京的朝阳区、海淀区、昌平区、丰台区等）

## 代码使用说明

可以方便的修改code和data，以查看更多城市、区、特定区域的宏观房产信息。只需要修改下面2处：

    - python/parse/main_lianjia_daily_self_crawl_and_parse.py 中的 city_id_list 赋值 （将来会把这个移到到配置文件中）
    - data/dict

## 个人技术博客

个人技术博客请访问 [vividfree的博客](http://vividfree.github.io/) 。
