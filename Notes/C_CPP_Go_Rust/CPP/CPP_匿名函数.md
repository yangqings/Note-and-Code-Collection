# CPP 匿名函数 Lambda 闭包

[TOC]

## 1、匿名函数的使用

匿名函数的基本语法为：

```c++
//[捕获列表](参数列表)->返回类型{函数体}
int main()
{
	auto Add = [](int a, int b)->int {
		return a + b;
	};
	std::cout << Add(1, 2) << std::endl;
	return 0;
}
```

上述代码便会输出3，这就是匿名函数的使用方法。

**注意点：一般情况下，编译器可以自动推断出lambda表达式的返回类型，所以我们可以不指定返回类型**，即：

```c++
//[捕获列表](参数列表){函数体}
int main()
{
	auto Add = [](int a, int b) {
		return a + b;
	};
	std::cout << Add(1, 2) << std::endl;
	return 0;
}
```

**但是如果函数体内有多个return语句时，编译器无法自动推断出返回类型，此时必须指定返回类型**

## 2、什么是捕获列表？

试图在Lambda内使用外部变量是错误的，例如：

```c++
#include <iostream>

int main()
{
	int c = 12;
	auto Add = [](int a, int b)->int {
		return c;
	};
	std::cout << Add(1, 2) << std::endl;
	return 0;
}
```

但是有些时候我们需要使用外部变量，所以需要使用捕获列表，上述代码改写成以下形式便可以通过编译。

```c++
#include <iostream>

int main()
{
	int c = 12;
	auto Add = [c](int a, int b)->int {
		return c;
	};
	std::cout << Add(1, 2) << std::endl;
	return 0;
}
```

但是如果你更改一下lambda表达式中代码块的内容，比如在上述代码中添加一句

```c++
c = a;
```

这样又会无法编译通过了，因为你的c是按值传递的，所以要将捕获列表改成

```c++
[&c](int a, int b)->int{……}；
```

这样c的值便是按引用传递了，便可以进行修改。

补充知识：

1. 如果捕获列表为[&]，则表示所有的外部变量都按引用传递给lambda使用
2. 如果捕获列表为[=]，则表示所有的外部变量都按值传递给lambda使用
3. 匿名函数构建的时候对于按值传递的捕获列表，会立即将当前可以取到的值拷贝一份作为常数，然后将该常数作为参数传递，即：

```c++
int main()
{
	int c = 12;
        //Add构建的时候实际是：[12](int a,int b)->int{}
	auto Add = [c](int a, int b)->int {
		return c;
	};
	std::cout << Add(1, 2) << std::endl;
	return 0;
}
```

**到此，匿名函数（Lambda表达式）的基础使用方法就介绍完毕了**

## 3、其他

### 3.1、Lambda

一个Lambda表达式表示一个可调用的代码单元，我们可以将它理解为一个未命名的内联函数。和任何函数类似，一个Lambda表达式具有**一个返回类型，一个参数列表和一个函数体**，但和普通函数不一样的是Lambda表达式可能定义在函数内部。**我们可以忽略Lambda表达式的参数列表和返回类型，但不可以忽略捕获列表和函数体**

```c++
//
//这是正确的（忽略了参数列表和返回类型）
//
//为什么没有指定返回类型还可以返回整数值？
//因为你的函数体有return语句，它可以推断出来
auto f = []{ return 1 + 2; };
```

### 3.2、Lambda捕获列表

|         []          | 空捕获列表，Lambda不能使用所在函数中的变量。                 |
| :-----------------: | :----------------------------------------------------------- |
|       [names]       | names是一个逗号分隔的名字列表，这些名字都是Lambda所在函数的局部变量。默认情况下，这些变量会被拷贝，然后按值传递，名字前面如果使用了&，则按引用传递 |
|         [&]         | 隐式捕获列表，Lambda体内使用的局部变量都按引用方式传递       |
|         [=]         | 隐式捕获列表，Lanbda体内使用的局部变量都按值传递             |
| [&,identifier_list] | identifier_list是一个逗号分隔的列表，包含0个或多个来自所在函数的变量，这些变量采用值捕获的方式，其他变量则被隐式捕获，采用引用方式传递，identifier_list中的名字前面不能使用&。 |
| [=,identifier_list] | identifier_list中的变量采用引用方式捕获，而被隐式捕获的变量都采用按值传递的方式捕获。identifier_list中的名字不能包含this，且这些名字面前必须使用&。 |

参考资料：《C++ Primer（第五版）》



## 4 博客文章

lambda表达式，闭包，std::function以及std::bind

### 4.1 lambda 表达式

C++11中新增了lambda 表达式这一语言特性。lambda表达式可以让我们快速和便捷的创建一个”函数”。

下面是lambda表达式的语法：

```
[ capture-list ] { body }`
`[ capture-list ] ( params ) { body }`
`[ capture-list ] ( params ) -> ret { body }`
`[ capture-list ] ( params ) mutable exception attribute -> ret { body }
```

这其中：

- **capture-list** 是需要捕获的变量列表，用逗号分隔。其详细说明见下文。

- **params** 是lambda表达式需要的参数列表，写法和函数参数一样，不过这里不支持默认参数。

- **ret** 指明了lambda表达式的返回值。通过return语句，如果编译器能够推断出返回值的类型。或者表达式没有返回值，“-> ret”可以省略。

- **body** 函数体。

- **mutable** 当捕获列表是以复制（见下文）的形式捕获时，默认这些复制的值是const的，除非指定了mutable。

- **exception** 提供了异常的说明。

- **attribute** 对于attribute的描述可以参见这里：http://en.cppreference.com/w/cpp/language/attributes，这里不多说明。

  下面，我们通过经典的`Hello World`示例来看一下lambda表达式：

```
auto lambda1 = [] {std::cout << "Hello, World!\n";};
lambda1();
```

这个lambda表达式将打印出字符串“Hello, World!”。
同时，我们将这个表达式赋值给“lambda1”这个变量，然后像调用函数一样，调用这个lambda表达式。

使用lambda表达式，可以让我们省却定义函数的麻烦，以inline的方式写出代码，这样的代码通常更简洁。
并且，由于阅读代码时不用寻找函数定义，这样的代码也更易读。

下面，我们来看另外一个例子。这个例子的需求是：
**分两次，打印出一个vector集合中，所有：**

**1. 模 5 = 0**
**2. 大于 20**

**的数字。**

现假设已有这个集合的定义如下：
`vector<int> numbers { 1, 2, 3, 4, 5, 10, 15, 20, 25, 35, 45, 50 };`

我们最先想到的方法自然是定义两个函数，分别按照上面的要求打印出需要的数字，它们的定义如下：

```
void printNumber1(vector<int>& numbers) {
	for (const int& i : numbers) {
	    if (i % 5 == 0) {
	        cout<<i<<endl;
	    }
	}
}

void printNumber1(vector<int>& numbers) {
	for (const int& i : numbers) {
	    if (i % 5 == 0) {
	        cout<<i<<endl;
	    }
	}
}
```

然后，我们在需要的地方，调用它们：

```
printNumber1(numbers);
printNumber2(numbers);
```


这里逻辑上并没有问题，但是：

1. 这里我们必须先定义这个函数，才能使用。而这样的函数，可能实际上我们只会使用一次。
2. 当工程大到一定程度，我们可能不记得每个函数的实现（所以函数命名很重要，原谅我这里给函数起了很含糊的名字，你在实际上工程中，请不要这样做），为了知道每个函数的实现，我们不得不查看函数的定义，这无疑给代码的阅读造成了一定的麻烦。

下面，我们来看看使用lambda表达式如何改善上面说的问题。
使用lambda表达式，我们可以这样写：

```
for_each(numbers.begin(), numbers.end(), [] (int i) {
	if(i % 5 == 0) {
	    cout<<i<<endl;
	}
});

for_each(numbers.begin(), numbers.end(), [] (int i) {
	if(i > 20) {
	    cout<<i<<endl;
	}
});
```

这里，我们不用单独定义函数，直接以inline的方式解决了问题。并且，这段代码一气呵成，你很直观的看到了执行的逻辑。

下面，我们再详细看一下lambda表达式中的捕获列表的语法，它可能是以下几种情况中的一种：

- [] 不捕获任何变量
- [&] 以引用的方式捕获所有变量
- [=] 以复制的方式捕获所有变量
- [=, &foo] 以引用的方式捕获foo变量，但是以复制的方式捕获其他变量
- [bar] 以复制的方式捕获bar变量，不再捕获任何其他变量
- [this] 捕获this指针

下面，我们再以一个例子说明捕获列表的用法。
这里，我们的需求是：
**打印出一个vector<int>的所有数字之和**

同样的，我们先以函数的方式来解决这个问题，这个函数的定义可以是这样的：

```
void printSum(vector<int>& numbers) {
	int sum = 0;
	for (const int& i : numbers) {
	    sum += i;
	}
	cout<<sum<<endl;
}
```

然后，我们在需要的地方调用这个函数：

```
vector<int> numbers { 1, 2, 3, 4, 5, 10, 15, 20, 25, 35, 45, 50 };
printSum (numbers);
```


而假设我们用lambda表达式来写，这样写就可以了：

```
vector<int> numbers { 1, 2, 3, 4, 5, 10, 15, 20, 25, 35, 45, 50 };
int sum = 0;
std::for_each(numbers.begin(), numbers.end(), [&sum] (const int& i) { sum += i;});
cout<<sum<<endl;
```

这里,我们用 **[&sum]**以引用的形式捕获了sum这个变量，并且在lambda表达式中修改了这个变量。
这样写，是不是比定义函数的方式简洁了很多？
对于这种，能够捕获其定义时上下文变量的函数，我们称之为“**闭包**”，下文还将提到。



### 4.2 std::function

上文中，对于**分两次，打印出一个vector集合中，所有：**
**1. 模 5 = 0**
**2. 大于 20**
**的数字。**
这个需求，我们的实现其实还不够好。

回头看一下printNumber1和printNumber2这两个函数，这两个函数大部分都是重复的：它们都需要遍历集合，都需要做if判断，然后打印出结果。
实际上，我们在项目中经常遇到这个的问题：
**两（多）个函数，有大部分的代码都是一样的，其中只有一两行代码有不一样的地方。**
其实，我们可以对这个**不一样**的地方，再做一个抽象，把它们共通起来。

具体到这个例子就是：无论是“模 5 = 0”还是“大于 20”都是满足“**某种条件**”。
而很自然的会想到，我们是否可以通过一个类似这样的函数来做这个判断：
`bool func(int i)`
然后实现两个函数，通过函数指针的形式来完成判断就好了。
但是，我们马上又意识到，这两个函数会很小，并且也是只会用一遍而已，定义一个函数又太“浪费”了。 很自然的，我们就会想lambda。但是，lambda似乎没法转成函数指针。。。

C++11中，提供了一个通用的描述方法，就是**std::function**。 std::function可以hold住任何可以通过“()”来调用的对象，包括：

- 普通函数
- 成员函数
- lambda
- std::bind（见下文）后的结果

std::function的语法是这样：
`template <class Ret, class... Args> class function<Ret(Args...)>;`

例如：`function<bool (int)> filter` 就表达了我们前面需要的那个函数：这个函数接受一个int值作为参数，同时返回一个bool作为判断的结果。但同时，**我们可以用lambda表达式直接传递进去。**

因此，上面的代码可以改写成这样：

```
void printNumber(vector<int>& number, function<bool (int)> filter) {
	for (const int& i : number) {
	    if (filter(i)) {
	        cout<<i<<endl;
	    }
	}
}
```

然后在需要的地方，这样调用即可：

```
printNumber(numbers, [] (int i){ return i % 5 == 0;});
printNumber(numbers, [] (int i){ return i > 20;});
```

这种做法，是不是又简洁了不少？



### 4.3 闭包

前面提到了“**闭包**”这个词，这里我们来聊一下闭包。

下面是维基百度对于闭包的定义：

**在计算机科学中，闭包（英语：Closure），又称词法闭包（Lexical Closure）或函数闭包（function closures），是引用了自由变量的函数。 这个被引用的自由变量将和这个函数一同存在，即使已经离开了创造它的环境也不例外。**

简单来说：闭包可以记忆住创建它时候的那些变量。
下面，我们再通过一个例子来说明。
现在，假设我们的需求是：**获取一个集合中最小和最大值，并在稍后的时候（可能是另外一个函数中）打印它们。** 这里，我们常规的做法通常是：通过一个函数获取集合的最大，最小值，然后保存住，最后在需要的时候访问这两个值，然后打印它们。
这样做就会需要解决：如果保存和传递最大，最小这两个值。
但实际上，这里我们可以考虑用闭包来实现这个功能，**让闭包把最大，最小两个值捕获下来**，然后在需要的地方调用就可以了。

请看一下下面这段代码：

```
void getMinMax(vector<int>& number, function<void ()>& printer) {
	int min = number.front();
	int max = number.front();
	for (int i : number) {
	    if (i < min) {
	        min = i;
	    }
	    if (i > max) {
	        max = i;
	    }
	}
	printer = [=] () {
	  cout << "min:" <<min<< endl;
	  cout << "max:" << max << endl;
	};
}
```

这里，我们通过`function<void ()>& printer`（如果你看不懂function，请看上文）传递出这个闭包。 然后，在需要的地方，这样即可：

```
function<void()> printer;
getMinMax(numbers, printer);
......

printer();
```

这里的printer其实是我们前面从getMinMax函数出传出的闭包，这个闭包捕获了min和max。我们直接传递这个闭包给需要的地方使用，而不用传递裸的两个数值，是不是优雅的不少？



### 4.4 std::bind

下面，我们再改进一下需求，假设我们要
**打印出vector<int>中，20<x<40范围内的值** ，该怎么办？
毕竟，`bool isBetween(int i, int min, int max)` 这个函数可没法对应上
`function<bool (int)> filter` 啊！参数数量就不一样嘛。
这个时候，我们可以用 **std::bind** 。

std::bind的语法是这样的：

```
template <class Fn, class... Args> bind (Fn&& fn, Args&&... args);
template <class Ret, class Fn, class... Args> bind (Fn&& fn, Args&&... args);
```

**std::bind可以将调用函数时的部分参数先指定好，留下一部分在真正调用的时候确定。**
（当然，你也可以直接指定全部参数，在调用时不再指定。）

这里，isBetween中，最小，最大值其实我们是确定了的，即：20和40。而不确定的，其实是真正待判断的数字本身，那么我们就可以这么做：
`std::bind(isBetween, placeholders::_1, 20, 40);`

**placeholders::_1** 的意思是，这里是一个占位符，在调用的时候，将实际传递的第一个参数放到这里。
占位符的数量可以是任意多的，像这样：
std::placeholders::_1, std::placeholders::_2, …, std::placeholders::_N。

于是乎，对于 **打印出vector<int>中，20<x<40范围内的值** 这个需求，我们在不修改printNumber函数的基础上，通过定义一个isBetween函数：

```
bool isBetween( int i, int min, int max) {
	return i >= min && i <= max;
}
```

然后，再这样就搞定了：

```
function<bool(int)> filter = std::bind(isBetween, placeholders::_1, 20, 40);
printNumber(numbers, filter);
```

当然，你甚至可以直接把这里的两行写成一行。

如果你不明白这段代码，请再看一下printNumber函数的定义：

```
void printNumber(vector<int>& number, function<bool (int)> filter) {
	for (const int& i : number) {
	    if (filter(i)) {
	        cout<<i<<endl;
	    }
	}
}
```

这里其实调用了filter(i)这个函数对象，而这个函数对象只接受一个int值作为参数，然后返回一个bool值。
`function<bool(int)> filter = std::bind(isBetween, placeholders::_1, 20, 40);`
绑定之后，只缺一个int型参数，所以正好对应得上。

如果不过瘾，我们再来看一个bind的例子。
我们常常需要在程序中，调用一些用户传过来的回调函数。而在回调函数中，用户常常会需要记录一些状态，于是常常希望通过一个对象的成员函数传给过来作为回调函数。但是在C++中，这样做是很麻烦的一个事情。因为，回调函数的类型我们很难定义。 但是，结合std::function和std::bind，一切变得容易多了。 结合前面的例子，现在就假设我们的回调函数是需要打印集合中的最大，最小值。这里假设我们是通过一个类来记录和打印值的，这个类的定义是这样的：

```
class Printer {
private:
	int min, max;
public:
	Printer(int x, int y) {
	    min = x;
	    max = y;
	}
	
	void print() {
	    cout << "min:" << min << endl;
	    cout << "max:" << max << endl;
	}
};
```

由于回调函数不需要参数，因此使用回调函数的代码是这样的：

```
void usingCallback(function<void ()> print) {
	print();
}
```

然后，我们可以通过下面的方法来调用print函数

```
Printer printer = Printer(10, 50);
function<void ()> print = bind(&Printer::print, printer);
usingCallback(print);
```

成员函数其实是类中的方法绑定到一个对象上，然后执行调用。这里的代码很直观的表达了这个关系。



### 4.5 lambda表达式是如何实现的

lambda表达式是如何实现的呢？

其实是编译器为我们了创建了一个类，这个类重载了()，让我们可以像调用函数一样使用。所以，你写的lambda表达式和真正的实现，是这个样子的：

<div align=center>
    <img src="pic/lambda/0 image_thumb.png" width="50%"/>
</div>



而对于捕获变量的lambda表达式来说，编译器在创建类的时候，通过成员函数的形式保存了需要捕获的变量，所以看起来是这个样子：
<div align=center>
    <img src="pic/lambda/1 image_thumb4.png" width="60%"/>
</div>

似乎也没有什么神奇的地方。但正是由于编译器帮我们实现了细节，使我们的代码变得优雅和简洁了许多。



### 4.6 参考资料

- http://www.cprogramming.com/c++11/c++11-lambda-closures.html
- http://www.drdobbs.com/cpp/lambdas-in-c11/240168241
- https://en.wikipedia.org/wiki/Closure_(computer_programming)
- http://www.jellythink.com/archives/771
- http://en.cppreference.com/w/cpp/utility/functional/function
- https://en.wikipedia.org/wiki/First-class_function
- https://blog.feabhas.com/2014/03/demystifying-c-lambdas/


原文地址：[《C++11中的lambda，std::function以及std:bind》](https://paul.pub/cpp-lambda-function-bind/) by [保罗的酒吧](https://paul.pub/)