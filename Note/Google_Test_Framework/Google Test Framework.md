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

如何控制printf打印的字体颜色（ANSI终端下）

参考后面的测试框架实现

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
#ifndef _MYTEST_H
#define _MYTEST_H

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

#endif
```

### 实现COLOR系列封装

```
\033[ A1;A2;A3...An m
```

```c
/**************************************************************
File Name: mytest.h
Author：Yang
***************************************************************/
#ifndef _MYTEST_H
#define _MYTEST_H

//COLOR封装
#define COLOR(msg, code) "\033[0;1;" #code "m" msg "\033[0m" 
//"#"表示字符串化，"#code"表示 "code"
#define RED(msg)    COLOR(msg, 31)
#define GREEN(msg)  COLOR(msg, 32)
#define YELLOW(msg) COLOR(msg, 33)
#define BLUE(msg)   COLOR(msg, 34)
i
//EXPECT封装
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

#endif
```

| 背景色  | 字体色  |            控制码             |                控制码                 |
| :-----: | :-----: | :---------------------------: | :-----------------------------------: |
|  40:黑  |  30:黑  |      \33[0m 关闭所有属性      |          \33[nB 光标下移n行           |
| 41:深红 |  31:红  |       \33[1m 设置高亮度       |          \33[nC 光标右移n行           |
|  42:绿  |  32:绿  |         \33[4m 下划线         |          \33[nD 光标左移n行           |
| 43:黄色 |  33:黄  |          \33[5m 闪烁          |         \33[y;xH 设置光标位置         |
| 44:蓝色 | 34:蓝色 |          \33[7m 反显          |              \33[2J 清屏              |
| 45:紫色 | 35:紫色 |          \33[8m 消隐          |     \33[K 清除从光标到行尾的内容      |
| 46:深绿 | 36:深绿 | \33[30m -- \33[37m 设置前景色 |          \33[s 保存光标位置           |
| 47:白色 | 37:白色 | \33[40m -- \33[47m 设置背景色 |          \33[u 恢复光标位置           |
|         |         |      \33[nA 光标上移n行       | \33[?25l 隐藏光标   \33[?25h 显示光标 |



### \__attribute__封装测试

```c
__attribute__((constructor))   //设置test函数属性，会先于main函数执行
void test(){
    
}

int main(){
    
}
```

注册测试函数，先于main函数执行，使用RUN_ALL_TEST方法调用所有测试函数



实现RUN_ALL_TEST

```c++
/**************************************************************
File Name: mytest.h
Author：Yang
***************************************************************/
#ifndef _MYTEST_H
#define _MYTEST_H

//COLOR封装
#define COLOR(msg, code) "\033[0;1;" #code "m" msg "\033[0m" 
//"#"表示字符串化，"#code"表示 "code"
#define RED(msg)    COLOR(msg, 31)
#define GREEN(msg)  COLOR(msg, 32)
#define YELLOW(msg) COLOR(msg, 33)
#define BLUE(msg)   COLOR(msg, 34)


//EXPECT封装
#define EXPECT(a,comp,b) { \
	__typeof(a) __a = (a), __b = (b); \
	if(!((__a) comp (__b))){ \
		printf(RED("%s:%d: Failure\n"), __FILE__, __LINE__);\
		printf(YELLOW("Expected: (%s) %s (%s), Actual: %d vs %d\n"), #a, #comp, #b, __a, __b); \
	} \
}
#define EXPECT_EQ(a, b) EXPECT(a, ==, b)
#define EXPECT_NE(a, b) EXPECT(a, !=, b)
#define EXPECT_LT(a, b) EXPECT(a, <, b)
#define EXPECT_LE(a, b) EXPECT(a, <=, b)
#define EXPECT_GT(a, b) EXPECT(a, >, b)
#define EXPECT_GE(a, b) EXPECT(a, >=, b)


//TEST封装
//__attribute__((constructor))为了实现先于main函数，执行测试函数注册
//这里展开了两处宏，一个生成reg##_##a##_##b()注册函数，一个生成测试执行的函数a##_##b()
#define TEST(a,b) \
void a##_##b(); \
__attribute__((constructor)) \
void reg##_##a##_##b() { \
    add_func(a##_##b, #a"."#b); \
} \
void a##_##b()


struct {
    void (*func)();        //函数指针（测试用例）
    const char *func_name; //函数名字（测试用例）
} func_arr[100];           //这里是固定100数组，实际工程应该考虑用链表实现
int func_cnt = 0;          //函数计数（测试用例）

void add_func(void(*func)(), const char *str){
    func_arr[func_cnt].func = func;
    func_arr[func_cnt].func_name = str;
    func_cnt += 1;
    return ;
}
    
//RUN_ALL_TEST封装
int RUN_ALL_TEST(){
    //执行每一个测试用例
    for(int i = 0; i < func_cnt; i++){
        printf(GREEN("[ RUN ]") "%s\n", func_arr[i].func_name);
        func_arr[i].func();  //执行测试函数
    }
    return 0;
}
#endif
```



测试用例：

```c++
#include <queue>
#include <stack>
#include <algorithm>
#include <string>
#include <map>
#include <set>
#include <vector>
#include "mytest.h"

using namespace std;



int myadd(int a, int b); 
int myminus(int a, int b); 

TEST(test, myadd){
	EXPECT_EQ(myadd(3,4), 7); // ==
	EXPECT_NE(myadd(3,4), 8); // !=
	EXPECT_GT(myadd(3,4), 6); // >
	EXPECT_GE(myadd(3,4), 6); // >=
	EXPECT_LT(myadd(3,4), 8); // <=
	EXPECT_LE(myadd(3,4), 6); // <   fault!
}

TEST(test, myminus){
	EXPECT_EQ(myminus(7,4), 3); // ==  
	EXPECT_NE(myminus(7,4), 4); // !=
	EXPECT_GT(myminus(7,4), 2); // >
	EXPECT_GE(myminus(7,4), 2); // >=
	EXPECT_LT(myminus(7,4), 1); // <= fault!
	EXPECT_LE(myminus(7,4), 1); // <  fault!
}

int myadd(int a, int b){
	return (a + b);
}

int myminus(int a, int b){
	return (a - b);
}

int main(void){
	printf(RED("hello world\n"));
	printf(GREEN("hello world\n"));
	printf(BLUE("hello world\n"));
	printf(YELLOW("hello world\n"));

    return RUN_ALL_TEST();
}
```

