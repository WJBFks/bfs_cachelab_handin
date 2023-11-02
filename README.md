# 实验准备
以ubuntu为例

## 安装valgrind
Valgrind是一款用于内存调试、内存泄漏检测以及性能分析的软件开发工具。本次实验中用来跟踪cache的命中情况。
```
    linux> apt-get install valgrind
```
或者
```
    linux> wget http://sourceware.org/pub/valgrind/valgrind-3.15.0.tar.bz2
    linux> tar -jxvf valgrind-3.15.0.tar.bz2
    linux> cd valgrind-3.15.0
    linux>./configure
    linux>make
    linux>make install
```

## 编译测试
进入实验文件夹，编译代码:
```
make
```

用.map文件来重排图,.map文件需要你自己编写程序生成:
```
chmod a+x permutate.sh
./permutate.sh ./data/XX.txt ./xx.map
```

将重排过后的图文件路径写在bfs中

测试:
```
./test-app -i ./bfs
```

清除生成文件:

```
make clean 
```

## 重排序*

使用`mapping.cpp`实现重排序

使用`g++`编译`cpp`代码：

```
g++ mapping.cpp -o mapping
```

查看帮助：

```
./mapping help
```

生成重排序后的图文件

```
./mapping ./data/XX.txt ./resort.map
```

> 其中`./data/XX.txt`为原始文件
>
> `./resort.map`为输出重排序后的文件，也可以使用别的文件名

修改`bfs.c`中的路径为`./resort.map`，或其他设置的重排序后的文件名

编译并运行

```
make && ./test-app -i ./bfs
```

## 文件清单

* Makefile     编译工具
* README       实验引导
* csim-ref*    cache分析模拟器
* bfs.c        bfs算法实现，需要修改其中的文件地址
* test-app.c   测试工具
* mapping.cpp* 重排序文件