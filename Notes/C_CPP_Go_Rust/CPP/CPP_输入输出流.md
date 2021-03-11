# CPP_输入输出流

<div align=center>
    <img src="pic/io/iostream.jpg" width="40%"/>
</div>

> 其中，图中的箭头代表各个类之间的派生关系。比如，ios 是所有流类的基类，它派生出 istream 和 ostream。特别需要指出的是，为了避免多继承的二义性，从 ios 派生出 istream 和 ostream 时，均使用了 virtual 关键字（虚继承）。

这些流类各自的功能分别为：

- istream：常用于接收从键盘输入的数据；
- ostream：常用于将数据输出到屏幕上；
- ifstream：用于读取文件中的数据；
- ofstream：用于向文件中写入数据；
- iostream：继承自 istream 和 ostream 类，因为该类的功能兼两者于一身，既能用于输入，也能用于输出；
- fstream：兼 ifstream 和 ofstream 类功能于一身，既能读取文件中的数据，又能向文件中写入数据。