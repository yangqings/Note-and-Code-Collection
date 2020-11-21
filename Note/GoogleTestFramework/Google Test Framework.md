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



### 谷歌测试框架基本使用流程

1. 编译gtest库，加入library

2. include头文件

3. 编写测试用例TEST

4. EXPECT系列宏
5. RUN_ALL_TESTS方法

### 彩色Printf

如何控制printf打印的字体颜色

ANSI终端下

示例：



### 宏定义

预处理命令--编译器内置宏

|          宏          |                  说明                   |
| :------------------: | :-------------------------------------: |
|      \__DATA__       |            日期：Mmm dd yyyy            |
|      \__TIME__       |             时间：hh:mm:ss              |
|      \__LINE__       |                  行号                   |
|      \__FILE__       |                 文件名                  |
|      \__func__       |      函数名/非标准（与编译器有关）      |
|      \__FUNC__       |      函数名/非标准（与编译器有关）      |
| \__PRETTY_FUNCTION__ | 更详细的函数信息/非标准（与编译器有关） |

例子：

```c
printf("__FILE__:%s",__FILE__);//输出文件名
printf("__LINE__:%d",__LINE__);//输出行号
printf("__FUNC__:%s",__FUNC__);//输出函数名
```

实现一个简单的LOG日志：

```c++
#include <queue>
#include <stack>
#include <algorithm>
#include <string>
#include <map>
#include <set>
#include <vector>

using namespace std;

#ifdef DEBUG
#define LOG(frm, args...){\
	printf("[%s : %d : %s]", __FILE__, __LINE__, __func__);\
	printf(frm, ##args);\
	pritnf("\n");\
}\
#else
#define  LOG(frm, args...)
#endif

void test(void){
	LOG("hello world");
	return;
}

int main(void){
    LOG("hello world");
    test();
    return 0;
}

```



预处理命令--条件式编译

|       函数       |         说明         |
| :--------------: | :------------------: |
|   #ifdef DEBUG   |  是否定义了DEBUG宏   |
|  #ifndef DEBUG   |  是否没定义DEBUG宏   |
|  #if MAX_N == 5  |   宏MAX_N是否等于5   |
| #elif MAX_N == 4 | 否则宏MAX_N是否等于5 |
|      #else       |                      |
|      #endif      |                      |



用条件编译加入DEBUG功能，打开DEBUG功能的方式：

1. 源码内定位DEBUG宏
2. 编译时加上-DEBUG编译选项

```shell
$ g++ -DEBUG xxx.cpp
```



宏定义展开命令，可以把宏定义展开，得到待编译源代码

``` shell
$ g++ -E xxx.cpp
```



### 实现EXPECT系列封装

如何实现自己的谷歌测试框架？

- 实现TEST
- 实现EXPECT
- 实现RUN_ALL_TEST



EXPECT实现：

```c++
/**************************************************************
File Name: mytest.h
Author：Yang
***************************************************************/

#define EXPECT(a, comp, p){\
	if(!((a) comp (b))){\
		printf("error\n");\
	}\
}
#define EXPECT_EQ(a, b) EXPECT(a, ==, b)
#define EXPECT_NE(a, b) EXPECT(a, !=, b)
#define EXPECT_LT(a, b) EXPECT(a, <, b)
#define EXPECT_LE(a, b) EXPECT(a, <=, b)
#define EXPECT_GT(a, b) EXPECT(a, >, b)
#define EXPECT_GE(a, b) EXPECT(a, >=, b)



```

### 实现COLOR系列封装