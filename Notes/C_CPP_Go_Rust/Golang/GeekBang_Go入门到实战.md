## 极客时间Go入门到实战

只记录这门课提到的比较重要的知识，基础知识在Go语言基础和课程ppt。

### 安装Go与环境搭建

1. Go安装

2. vscode

3. 解决vscode go tools安装失败



### 测试工具使用

1. 代码测试框架

2. vscode output窗口显示log信息

### 第五章 函数

#### 可变参数

#### defer函数

直接简单的理解就是，defer函数会在函数执行完后被执行，即使是panic错误，也会被执行，可以用来释放资源，比如释放锁、关闭连接



### 第六章 面向对象编程

封装数据和行为

Go不支持继承，通过符复合的方式来复用



- panic用于不可恢复的错误
- panic退出时会执行defer指定的内容

panic vs os.Exit

- os.Exit退出时不会调用defer指定的函数
- os.Exit退出时不会输出当前调用栈信息

### 第九章 并发编程

#### Goroutine协程

协程是轻量级的线程



#### 共享内存并发控制

Mutex



WaitGroup



### CSP并发机制

Communicating sequential processes





#### 多路选择与超时

select 超时机制