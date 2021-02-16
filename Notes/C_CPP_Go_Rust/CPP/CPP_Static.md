# CPP_Static

### 静态变量

- 函数中的静态变量，空间将在整个程序生命周期内分配。即使**多次调用该函数**，静态变量的空间也**只分配一次。**

- 类中的静态变量：声明的static变量只被初始化一次，因为它在单独的静态存储中分配了空间，类中的静态变量由对象共享。对于不同的对象，不同有相同的静态变量的多个副本。因此，静态变量不能使用构造函数初始化。

```c++
#include <iostream>
using namespace std;

class Apple{
  public:
    static int i;
    Apple(){
        
    };
};

int main()
{
	Apple obj1;
    Apple obj2;
    obj1.i = 2;//通过为多个对象创建多个静态变量i的副本
    obj2.i = 3;
    cout<<obj1.i<<" "<<obj2.i;//结果没有发生
}

//必须显示初始化
int Apple::i = 1;

int main()
{
    Apple obj
    cout<<obj.i;//输出 1
}
```



### 静态成员

- 类对象为静态：

```c++
#include<iostream> 
using namespace std; 

class Apple 
{ 
    int i; 
    public: 
        Apple() 
        { 
            i = 0; 
            cout << "Inside Constructor\n"; 
        } 
        ~Apple() 
        { 
            cout << "Inside Destructor\n"; 
        } 
}; 

int main() 
{ 
    int x = 0; 
    if (x==0) 
    { 
        Apple obj; 
    } 
    cout << "End of main\n"; 
} 

//输出
Inside Constructor
Inside Destructor
End of main
```

```c++
#include<iostream> 
using namespace std; 

class Apple 
{ 
    int i; 
    public: 
        Apple() 
        { 
            i = 0; 
            cout << "Inside Constructor\n"; 
        } 
        ~Apple() 
        { 
            cout << "Inside Destructor\n"; 
        } 
}; 

int main() 
{ 
    int x = 0; 
    if (x==0) 
    { 
        static Apple obj; 
    } 
    cout << "End of main\n"; 
} 

//输出
Inside Constructor
End of main
Inside Destructor
```

静态对象的生命周期是程序的生命周期。



- 类中的静态函数

静态成员函数不依赖类的对象，可以使用' . '来调用静态成员函数。

**允许**静态成员函数**仅访问静态数据成员或者其他静态成员函数**，它们**无法访问**类的**非静态**数据成员或者成员函数(因为不接受隐含的this自变量)。

```c++
#include <iostream>
using namespace std;

class Apple{
    public:
    	static void printMsg{
            cout<<"Welcome to Apple!";
        }
};

int main()
{
    Apple::printMsg();
}

//输出
Welcome to Apple!
```

### 静态成员函数和普通函数区别

- 作用域区别：