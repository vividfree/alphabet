# alphabet

欢迎来到 vividfree 的 alphabet代码仓库，这个仓库将放置 Machine Learning / Natural Language Processing / Big Data Computing 相关的代码，主要用 C++ / Python / Shell 语言开发。

## 仓库目录的整体介绍

    - src : 源代码
      - base : 基础库
        - cpp    :    C++相关的基础库
        - python : Python相关的基础库
        - shell  :  Shell相关的基础库
      - machine_learning             : 项目"机器学习"
      - sparse_matrix_multiplication : 项目"基于MapReduce开发的稀疏矩阵相乘"

## 项目目录的结构说明

一般而言，项目下会包括如下几个子目录：

    - bin      : 编译 C / C++ 得到的可执行程序
    - build.sh : 项目的打包脚本
    - conf     : 项目的配置文件
    - data     : 项目的数据文件
    - python   : 项目的 Python  相关源代码
    - shell    : 项目的 Shell   相关源代码
    - src      : 项目的 C / C++ 相关源代码

1. build.sh 是项目的打包脚本。一般情况下开发机与线上机器是不同的机器，打包脚本能方便项目部署。
2. 项目一般会包括多个模块，各个模块一般都需要准备单测文件，甚至是测试数据。模块的单测文件和单测所用的测试数据就放在对应的模块中，这样方便系统维护（比如回归测试）。
3. src子目录主要存放的是 C / C++ 相关源代码，子目录名没有像base基础库中取名为cpp，是因为src子目录下还会放单测脚本和测试数据，内容较多。另外src目录一般不用被build.sh用于项目打包。
