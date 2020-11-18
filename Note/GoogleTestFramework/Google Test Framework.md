## Google Test Framework

### 谷歌针对C和C++的测试框架

将需要测试的新功能函数作为模块，链接成为可执行程序。

![](pic\pic1.png)

### CMake

一般使用流程：

建立build文件夹，进入build文件夹

```bash
$ CMake  ../
```

在build文件夹，复制编译需要的源码，生成make文件

执行make命令，开始编译