# thirdparty目录说明

src目录下有一些常用的库(tar.gz 或者 zip 格式)，每个库都有对应的 install_xxx.sh 安装脚本，执行安装脚本，便会在 thirdparty 下生成编译好的目录。

## 示例
进入 thirdparty/src ，执行 sh install_boost_1.52.0.sh ，会在 thirdparty 目录下产生 boost_1.52.0 目录，其中含有include和lib子目录。
