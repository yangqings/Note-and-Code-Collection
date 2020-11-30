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