## GSOA_CETSP

根据SOM改进的方法GSOA，解决CETSP问题，论文出处

```
@article{faigl18jfr,
   author    = {Jan Faigl and Petr Vana and Robert Penicka and Martin Saska},
   title     = {Unsupervised Learning based Flexible Framework for Surveillance Planning with Aerial Vehicles},
   journal   = {Journal of Field Robotics},
   year      = {2018},
   note      = {In press}
}
```

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

|                函数名称                |      功能      |    参数    | 返回值 |
| :------------------------------------: | :------------: | :--------: | :----: |
|    int main(int argc, char *argv[])    |   main主函数   | 命令行参数 |        |
| bool parseArgs(int argc, char *argv[]) | 解析命令行参数 | 命令行参数 |        |
|                                        |                |            |        |

### gsoa_cetsp_bezier.cc

`cetsp-bezier-gsoa/src/gsoa_cetsp_bezier.cc`，主要的算法在这个源文件。

**部分重要函数**

|                          函数名称                          |                            功能                            |               参数               |    返回值    |
| :--------------------------------------------------------: | :--------------------------------------------------------: | :------------------------------: | :----------: |
|          void CGSOACETSPBezier::iterate(int iter)          |                GSOA算法无监督学习的迭代过程                |   迭代次数 -1表示完成所有迭代    |     void     |
| double CGSOACETSPBezier::refine(int step, double errorMax) |      主要的winner select和adapt过程都在这个函数被调用      | 当前迭代步数；允许的最大路径误差 | 路径误差总和 |
|      void CGSOACETSPBezier::ring_regenerate(int step)      | 根据每次refine函数迭代生成的目标点访问序列，生成bezier曲线 |           当前迭代步数           |     void     |

**部分重要参数**

|                           参数名称                           |              参数功能               | 默认值 |
| :----------------------------------------------------------: | :---------------------------------: | :----: |
|                         param-change                         | 无监督学习的学习率的参数变化方式；  | somhom |
|                        learning-rate                         |             初始学习率              |  0.5   |
|                     gain-decreasing-rate                     |             增益衰减率              |  0.1   |
|                    neuron-number-headings                    |                                     |   3    |
|                  icann-gain-decreasing-rate                  |             增益衰减率              | 0.0005 |
|                     neighborhood-factor                      | 邻节点因子，在Winner Select过程有用 |  0.2   |
| max-horizontal-speed=5<br/>max-horizontal-accel=2<br/>max-vertical-speed=1<br/>max-vertical-accel=1 |     Robot的最大速度和加速度限制     |  ...   |
| bezier-optimization-step=0.005<br/>bezier-optimization-max=200<br/>bezier-optimization-cycles=3<br/>bezier-samples=200<br/>bezier-samples-visual=20 |        Bezier曲线相关的参数         |  ...   |

```c++
config.add<std::string>("param-change", "somhom|icann", "somhom");

config.add<std::string>("ring-length", "ring_euclid|ring_time", "ring_eulid");

config.add<double>("learning-rate", "neuron adaptation parametr in activation function mi*exp(d)", 0.6);

config.add<double>("number-neurons-multiplication","multiplication parametr to get number of neurons as multiplication of number of cities", 2.5);

config.add<double>("gain-decreasing-rate", "Decrasing rate, higher value means faster convergence", 1e-4);

config.add<double>("neighborhood-factor", "factor to compute number of neighborhood neurons as division of number of neurons, neighborhood are considered on both sides (left, right) of winning neuron so d*2 neurons are moved ", 5);

config.add<int>("termination-max-steps", "Stop adaptation if number of steps is large than given", 180);

config.add<double>("termination-error", "Stop adaptation when the current error is less than this value", 0.001);

config.add<bool>("best-path", "Enable/disable considering best path found during the evaluation", false);

config.add<int>("neuron-number-headings", "Number of alternative headings per neuron for each direction", 10);

config.add<bool>("alternate-target", "Enable/disable alternate target, the winner is not set to the presented target", true);

config.add<int>("vehicles", "Number of vehicles", 1);

config.add<std::string>("start-targets", "A list of target labels (starting from 0) that denote the starting locations (separated by ','). Must match with number of vehicles", "0");

config.add<double>("icann-gain-decreasing-rate", "Decrasing reate for the icann param change, higher value means faster convergence", 1e-4);

config.add<bool>("ring-regenerate-min-distance", "If enabled only neurons that are a bit far from each other are preserved", true);

config.add<bool>("ring-regenerate-preserve-active", "If enabled also active neurons are preserved in the ring regeneration", true);

config.add<bool>("force-zero-error-quit", "If enabled, the adaptation is termined when winners fit the targets and the solution is not improving", true);
```

**伪代码:**

<div align=center>
    <img src="pic/0 code.png" width="70%"/>
</div>

<div align=center>
    <img src="pic/1 adapt.png" width="100%"/>
</div>



### generate_random_problem.cc

`cetsp-bezier-gsoa/src/generate_random_problem.cc`，在原工程基础上添加的源码，主要用来生成随机的数据集，在原工程所有代码被执行之前调用。

| 函数名称 | 功能 | 参数 | 返回值 |
| :------: | :--: | :--: | :----: |
|          |      |      |        |
|          |      |      |        |
|          |      |      |        |