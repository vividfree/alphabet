# CGI服务的demo

## 背景

为了保证服务的性能，网络服务常用C++语言开发。对于用C++语言搭建服务，常见的一种框架是nginx + CGI/fastCGI。因为处理request和产出response大体是调用一些接口做一些业务上的开发，所以可以稍微做个封装，形成一个大体上可用的CGI服务框架，比如：
+ 检测POST形式的request如何取数据；
+ 判断是否为合法request；
+ 如何以json格式产出response数据（含服务返回的状态码和信息）。

有了一个大体框架后，将来可以用于快速搭建业务所需的server（当然如果对QPS、latency等有要求的话，还需要优化代码）。

## 系统的大体情况

+ 代码质量方面
  - 总体上遵照Google C++开发风格，比如：
    - 头文件保护
    - include文件的顺序
    - 类或者结构的前置申明
    - 命名方式
  - 对输入输出做了恰当的异常检测；
  - 对代码做了恰当的抽象，尽量减少冗余代码。

## 目录的整体介绍

    - conf : 配置文件
    - cplusplus : C++代码
      - def_struct: 定义request数据结构和response数据结构（含服务返回的状态码和信息）
      - engine : CGI服务的核心（当做引擎）
      - main : CGI服务的main()函数
      - request : 对request的处理接口，包括检测request是否合法以及读取request中的数据
      - response : 对response的处理接口
      - util : 若干工具接口
        - config.h : 读取ini格式的接口

## TODO

是否线程安全还需要测试：
+ 除了调用的底层接口（比如boost, fcgi, gflag, glog, jsoncpp）外，笔者自行开发的代码会尽可能保证线程安全。
+ 但是该demo的代码暂时还不能保证线程安全，因为有2处还未做详细测试，一个是jsoncpp的若干接口是否线程安全，一个是C++ new操作是否线程安全。

这是后续优先要做的工作。
