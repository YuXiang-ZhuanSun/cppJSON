# 项目介绍

本项目使用c++，建立了用于表示[JSON](https://www.json.org/json-en.html)的数据结构。

* 实现了将JSON结构可视化输出的功能

* 将实现从JSON字符串解析成自定义JSON数据结构的功能



本项目使用[小熊猫dev-c](https://royqh.net/devcpp/download)开发。但可移植到各种环境中运行。

其中：

* cppJSON.h 是核心库文件，内含构建JSON结构的各种函数
* main.cpp是展示了将JSON结构可视化的多个样例


# 核心技术

* 使用一个异质链表结构存储JSON
* 不同种类的元素由派生类模板存储
* 通过基类指针，遍历整个异质链表
* 本结构还使用了虚函数，输出运算符重载等



使用愉快，后续会更新将字符串解析成JSON功能。

参考：
* [cJSON](https://github.com/DaveGamble/cJSON)
