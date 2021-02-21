## GSOA_CETSP

根据SOM改进的方法GSOA，解决CETSP问题，论文出处

### compile & install

工程目录结构如下：

```c
.
├── cetsp-bezier-gsoa          //主要目录
│   ├── CMakeLists.txt        
│   ├── etc                    //txt文本格式保存CETSP问题的坐标数据
│   ├── src                    //主要源码目录
│   └── tcetsp-bezier-gsoa.cfg //配置文件，仿真程序通过读取该文件配置求解器和GUI
├── clean-cmake_build.sh       //运行脚本清除所有编译文件
├── CMakeLists.txt             //Cmake文件
├── crl                        //Common Robot Library 依赖的库文件，暂时不需要修改
│   ├── clean-cmake_build.sh
│   ├── clean.sh
│   ├── cmake
│   ├── CMakeLists.txt
│   ├── crl
│   ├── crl.algorithm
│   ├── crl.gui
│   ├── crl.loader
│   ├── crl.tsplib
│   ├── install-cmake_build.sh
│   ├── install.sh
│   ├── LICENSE
│   ├── Mk
│   └── README.md
├── install-cmake_build.sh    //运行脚本编译工程，编译后的可执行程序在build目录下
├── paper                     //论文 
└── README.md
```

主要依赖如下：

|          名称           |             功能              |
| :---------------------: | :---------------------------: |
|        Log4cxx库        |  Logger库，用于打印调试日志   |
|         Boost库         |                               |
|         Cairo库         |          用于GUI绘图          |
| C++ 11标准、G++ 、CMake | C++标准、编译器、编译管理工具 |

1. 安装依赖

```shell
#安装boost库
$sudo apt-get install libboost-all-dev

#安装cairo库
$sudo apt-get install python-cairo 
$sudo apt-get install libcairo2
```

log4cxx库需要自行下载源码和依赖，然后编译，[教程](https://blog.csdn.net/qq_19288615/article/details/78182492?depth_1-utm_source=distribute.pc_relevant.none-task-blog-BlogCommendFromBaidu-2&utm_source=distribute.pc_relevant.none-task-blog-BlogCommendFromBaidu-2)。

- 编译

   进入工程目录，执行命令

   ```shell
   $sudo ./install-cmake_build.sh
   ```

- 运行

   进入build目录，运行程序

   ```shell
   $./tcetsp-bezier-gsoa
   ```

   加上 `--help`查看帮助，有几个配置仿真的option（可以修改cfg文件配置，也可以用命令行参数配置）

   - General options

   - GUI options

   - Solver options

### tcetsp-bezier-gsoa.cc

`cetsp-bezier-gsoa/src/tcetsp-bezier-gsoa.cc`，主函数入口在这个源文件中

|                函数名称                |      功能      | 参数 | 返回值 |
| :------------------------------------: | :------------: | :--: | :----: |
|    int main(int argc, char *argv[])    |   main主函数   |      |        |
| bool parseArgs(int argc, char *argv[]) | 解析命令行参数 |      |        |
|                                        |                |      |        |

### gsoa_cetsp_bezier.cc

`cetsp-bezier-gsoa/src/gsoa_cetsp_bezier.cc`，主要的算法在这个源文件。

| 函数名称 | 功能 | 参数 |
| :------: | :--: | :--: |
|          |      |      |
|          |      |      |
|          |      |      |



### generate_random_problem.cc

`cetsp-bezier-gsoa/src/generate_random_problem.cc`，在原工程基础上添加的源码，主要用来生成随机的数据集，在原工程所有代码被执行之前调用。

| 函数名称 | 功能 | 参数 |
| :------: | :--: | :--: |
|          |      |      |
|          |      |      |
|          |      |      |