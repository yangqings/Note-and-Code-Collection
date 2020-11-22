## CPP_Virtual_Function

- 普通成员函数属性---->类

普通成员函数被调用，是根据标识符的类属性来调用；

- 虚函数成员属性----->对象

虚函数被调用，是根据标识符的对象类型属性来调用；

虚函数

```c++
#include <algorithm>
#include <string>
#include <map>
#include <set>
#include <vector>

using namespace std;

class A{
public:
	virtual void say(int x){
        cout << this << endl; 
        cout << "class A: " << x <<endl;
    }    
}

class B: public A{
public:
	void say(int x) override{
        cout << this << endl; 
        cout << "class B: " << x <<endl;
    }
}

typedef void (*func)(void *, int x);

int main()
{
    cout<< sizeof(B) << endl;
    B b;
    A &a = b;
    A *c = &b;
    ((func **)(&b))[0][0](&b, 123); //调用了虚函数
    a.say(123);
    b.say(123);
    c.say(123);
    return 0;
}
```

