## MIT6.S081 & 6.828

### Lec1 介绍

------

#### 1.1 课程内容 

- OS Interface

- 为什么fork和exce要分开实现？

  因为....

Operating system organization，操作系统三大要求

- multiplexing
- isolation
- interaction

monolithic kerne 单内核

#### 2.1 Lab

##### 安装环境与编译系统

[Xv6 and Unix utilities]()

系统：ubuntu18.04-LTS

- step1 获取实验代码

```sh
$ git clone git://g.csail.mit.edu/xv6-labs-2020
Cloning into 'xv6-labs-2020'...
...
$ cd xv6-labs-2020
$ git checkout util
```

- step2 [安装tools](https://pdos.csail.mit.edu/6.828/2020/tools.html)

```shell
sudo apt-get install git build-essential gdb-multiarch qemu-system-misc gcc-riscv64-linux-gnu binutils-riscv64-linux-gnu 
```

`注意`交叉编译器的版本：ubuntu默认的gcc-7-riscv64-linux-gnu不支持-mno-relax选项，需要卸载gcc-7-riscv64-linux-gnu并安装gcc-8-riscv64-linux-gnu；然后创建链接/usr/bin/riscv64-linux-gnu-gcc指向/usr/bin/riscv64-linux-gnu-gcc-8

```shell
$ sudo apt-get install gcc-8-riscv64-linux-gnu
```

```shell
$ update-alternatives --install /usr/bin/riscv64-linux-gnu-gcc riscv64-linux-gnu-gcc /usr/bin/riscv64-linux-gnu-gcc-8 1
```

`注意` ubuntu apt安装的qemu版本太老，缺失qemu-system-riscv64

下载qemu并编译安装

```shell
$ wget https://download.qemu.org/qemu-5.1.0.tar.xz
$ tar xf qemu-5.1.0.tar.xz
```

```shell
$ cd qemu-5.1.0
$ ./configure --disable-kvm --disable-werror --prefix=/usr/local --target-list="riscv64-softmmu"
$ make
$ sudo make install
$ cd ..
```

编译过程有缺失依赖再另外google解决。

- step3 进入Lab code文件夹编译并启动xv6系统

```shell
# in the xv6 directory
$ make qemu
# ... lots of output ...
init: starting sh
$
```

##### 实现一个sleep程序

```c

```

### Lec2 C & GDB

------





### Lec3 OS组织和系统调用

------





### Lec4 页表

------

