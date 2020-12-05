# 侯捷C++系列学习笔记

## 基础课：C++面向对象高级开发

C++版本：C++98(1.0)、03、11(2.0)、14、20

### 1 参数传递与返回值

#### 1.1 把构造函数写成private成员函数

```c++
class A{
    static A& getInstance();
    setup() {...}
private:
    A();
    A(const A& rhs);
    ....
    
}

A& A::getInstance()
{
    static A a;
    return a;
}

//只能通过
A::getInstance.setup();
```

这是单例设计模式，只能通过`A::getInstance.setup()`获得唯一的对象；

#### 1.2 传递const参数

对于传递参数，不会被函数内部改变的参数的应该被声明为const，const指针可以指向普通指针，但是普通指针无法指向const指针。

#### 1.3 传递引用reference

尽量传引用，不传value，如果不允许被修改，应该把引用声明为const；

传引用与传指针的区别，指针没有拷贝，引用有拷贝，在函数内部堆参数引用改变

#### 1.4 friend 友元

- 被声明为友元的函数可以直接取类内私有成员数据；友元打破了封装的特性；

- 相同class的各个object互为友元；

  比如不同的object的函数成员方法可以直接处理不同的object；

```
inline complex&
__doapl(complex* ths, const complex& r)
{
	ths->re += r.re; //第一参数被改变
    ths->im += r.im; //第二参数不被改变
    return *ths;
}
```

#### 1.5 return by reference

不可以返回局部变量local object的reference；

传递者不需要知道接收者是以reference形式接收

### 2 操作符重载

任何成员函数都有一个隐藏的this pointer，指向对象本身；

操作符重载有两种写法：成员函数写法、非成员函数写法；

#### 2.1 成员函数的操作符重载

重载操作符为什么需要返回对象的reference? **考虑多个操作符连用的情况；**多个操作符连用的时候，前面步骤完成的返回应该是对象reference，这样可以继续执行操作符，如果是void则不行；

`typename();`创建临时对象，用来return value；

临时对象声明执行完，下一行就消失了；

### 3 拷贝构造、拷贝复制、析构



## C++内存管理



## STL源码剖析



## C++STL与泛型编程



## C++11新特性

