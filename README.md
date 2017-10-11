# alphabet

欢迎来到 vividfree 的 alphabet 代码仓库，这个仓库将放置 Machine Learning / Natural Language Processing / Big Data Computing 相关的代码，主要用 C++ / Python / Shell 语言开发。个人技术博客请访问 [vividfree的博客](http://vividfree.github.io/) 。

## 仓库目录的整体介绍

    - src : 源代码
      - base : 基础库
        - cpp    : C++    相关的基础库
        - python : Python 相关的基础库
          - file_util : 文件处理相关的基础接口 
          - path_util : 路径相关的基础接口
          - text_util : 文本处理相关的基础接口
          - util      : 其他基础接口
        - shell  : Shell  相关的基础库
      - cgi_demo  : 项目"CGI服务的demo" （虽然是demo，但工程框架做得比较好，适合在该基础上开发真实的CGI服务）
      - crawl_and_analyse_website    : 项目"爬取和解析某些网站"
        - analyse_lianjia  : 子项目"爬取和解析链家的某些网页"
      - machine_learning             : 项目"机器学习"
      - sparse_matrix_multiplication : 项目"基于MapReduce开发的稀疏矩阵相乘"
      - tool : 工具库

说明：
* 对C++，常用nginx + fastCGI搭建HTTP服务

## 项目目录的结构说明

一般而言，项目下会包括以下几个子目录或者文件：

    - bin       : 编译 C / C++ 得到的可执行程序
    - build.sh  : 项目的打包脚本
    - conf      : 项目的配置文件
    - cplusplus : 项目的 C / C++ 相关源代码
    - cpp       : 项目的 C / C++ 相关源代码
    - data      : 项目的数据文件
    - python    : 项目的 Python  相关源代码
    - shell     : 项目的 Shell   相关源代码

1. build.sh 是项目的打包脚本。一般情况下开发机与线上机器是不同的机器，打包脚本能方便项目部署。
2. 项目一般会包括多个模块，各个模块一般都需要准备单测文件，甚至是测试数据。模块的单测文件和单测所用的测试数据就放在对应的模块中，这样方便系统维护（比如回归测试）。
