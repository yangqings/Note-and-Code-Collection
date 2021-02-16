# C++_新特性 C++ 11 14 17 20

参考书籍：[《现代C++教程： 高速上手C++ 11/14/17/20》](https://changkun.de/modern-cpp/zh-cn/00-preface/)

## 1 被弃用的特性

直接学习新的特性，向新技术标准靠拢

从C++11开始被弃用的特性：

- **不再允许字符串字面值常量赋值给一个 `char \*`。如果需要用字符串字面值常量赋值和初始化一个 `char \*`，应该使用 `const char \*` 或者 `auto`。**

  ```c++
  char *str = "hello world!"; // 将出现弃用警告
  ```

- **C++98 异常说明、 `unexpected_handler`、`set_unexpected()` 等相关特性被弃用，应该使用 `noexcept`。**

- **`auto_ptr` 被弃用，应使用 `unique_ptr`。**

- **`register` 关键字被弃用，可以使用但不再具备任何实际含义。**

- **`bool` 类型的 `++` 操作被弃用。**

- **如果一个类有析构函数，为其生成拷贝构造函数和拷贝赋值运算符的特性被弃用了。**

- **C 语言风格的类型转换被弃用（即在变量前使用 `(convert_type)`），应该使用 `static_cast`、`reinterpret_cast`、`const_cast` 来进行类型转换。**

- **特别地，在最新的 C++17 标准中弃用了一些可以使用的 C 标准库，例如 `<ccomplex>`、`<cstdalign>`、`<cstdbool>` 与 `<ctgmath>` 等**

- ……等等

## 2 语言可用性强化

### 2.1 常量

- nullptr： 代替NULL表示空指针
- constexpr： C++11 提供了 `constexpr` 让用户显式的声明函数或对象构造函数在编译期会成为常量表达式

### 2.2 变量

- 初始化列表 `std::intializer_list`

- 结构化绑定 `std::tuple`元组容器，C++17的结构化绑定，方便对元组容器拆解

  ```c++
  #include <iostream>
  #include <tuple>
  
  std::tuple<int, double, std::string> f() {
      return std::make_tuple(1, 2.3, "456");
  }
  
  int main() {
      auto [x, y, z] = f();
      std::cout << x << ", " << y << ", " << z << std::endl;
      return 0;
  }
  ```

### 2.3 类型推导

- `auto` ，`decltype`关键字（C++11后）
  - auto不能用于函数传参
  - auto不能用于推导数组类型

- `decltype` 关键字是为了解决 `auto` 关键字只能对变量进行类型推导的缺陷而出现的。它的用法和 `typeof` 很相似：

  ```c++
  decltype(表达式)
  ```

  有时候，我们可能需要计算某个表达式的类型，例如：

  ```c++
  auto x = 1;
  auto y = 2;
  decltype(x+y) z;
  ```

  你已经在前面的例子中看到 `decltype` 用于推断类型的用法，下面这个例子就是判断上面的变量 `x, y, z` 是否是同一类型：

  ```c++
  if (std::is_same<decltype(x), int>::value)
      std::cout << "type x == int" << std::endl;
  if (std::is_same<decltype(x), float>::value)
      std::cout << "type x == float" << std::endl;
  if (std::is_same<decltype(x), decltype(z)>::value)
      std::cout << "type z == type x" << std::endl;
  ```

  其中，`std::is_same<T, U>` 用于判断 `T` 和 `U` 这两个类型是否相等。输出结果为：

  ```c++
  type x == int
  type z == type x
  ```

## 3 语言运行时强化

### 3.1 Lambda表达式（重要）



### 3.2 函数对象包装器



### 3.3 右值引用（重要）