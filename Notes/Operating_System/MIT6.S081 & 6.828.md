

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

To quit qemu type: `Ctrl-a x`

##### 实现一个sleep程序

> Implement the UNIX program sleep for xv6; your sleep should pause for a user-specified number of ticks. A tick is a notion of time defined by the xv6 kernel, namely the time between two interrupts from the timer chip. Your solution should be in the file user/sleep.c. 

> Some hints:
>
> - Before you start coding, read Chapter 1 of the xv6 book.
> - Look at some of the other programs in user/ (e.g., user/echo.c, user/grep.c, and user/rm.c) to see how you can obtain the command-line arguments passed to a program.
> - If the user forgets to pass an argument, sleep should print an error message.
> - The command-line argument is passed as a string; you can convert it to an integer using atoi (see user/ulib.c).
> - Use the system call sleep.
> - See kernel/sysproc.c for the xv6 kernel code that implements the sleep system call (look for sys_sleep), user/user.h for the C definition of sleep callable from a user program, and user/usys.S for theassembler code that jumps from user code into the kernel for sleep.
> - Make sure main calls exit() in order to exit your program.
> - Add your sleep program to UPROGS in Makefile; once you've done that, make qemu will compile your program and you'll be able to run it from the xv6 shell.
> - Look at Kernighan and Ritchie's book The C programming language (second edition) (K&R) to learn about C. 

源码写在lab/user/sleep.c 

```c
/**
 * @file sleep.c
 * @author YangQingsheng
 * @brief Implement the UNIX program sleep for xv6
 * @version 0.1
 * @date 2021-02-08
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char *argv[])
{
    int seconds;
    if(argc != 2){
        fprintf(2, "usage: sleep [seconds]\n");
        exit(1);
    }

    seconds = atoi(argv[1]);

    if(seconds < 0){
        fprintf(2, "sleep: parameter error\n");
        exit(1);
    }

    sleep(seconds);
    //fprintf(2, "sleep %d seconds done\n",seconds);

    exit(0);
}
```

在Makefile的UPROGS添加_sleep

执行`make grade` 测试代码

##### 实现一个pingpong程序

> Write a program that uses UNIX system calls to ''ping-pong'' a byte between two processes over a pair of pipes, one for each direction. The parent should send a byte to the child; the child should print "<pid>: received ping", where <pid> is its process ID, write the byte on the pipe to the parent, and exit; the parent should read the byte from the child, print "<pid>: received pong", and exit. Your solution should be in the file user/pingpong.c.
>

> Some hints:
>
> - Use pipe to create a pipe.
> - Use fork to create a child.
> - Use read to read from the pipe, and write to write to the pipe.
> - Use getpid to find the process ID of the calling process.
> - Add the program to UPROGS in Makefile.
> - User programs on xv6 have a limited set of library functions available to them. You can see the list in user/user.h; the source (other than for system calls) is in user/ulib.c, user/printf.c, and user/umalloc.c. 

思路，两个管道，父进程通过管道1发送，子进程接收到内容后，通过管道2发送，父进程接收

源码

```c
#include "kernel/types.h"
#include "user/user.h"

int main(int argc, char *argv[])
{
    int pipe1_p2c[2],pipe2_c2p[2];//two pipe, pipe[0]:read, pipe[1]:wirte
    char buffer[] = {'Y'};
    long length = sizeof(buffer);
    pipe(pipe1_p2c);   
    pipe(pipe2_c2p);



    if(fork() == 0){ //child
        close(pipe1_p2c[1]);
        close(pipe2_c2p[0]);

        if(read(pipe1_p2c[0],buffer,length) != length){
            printf("parent--pipe-->child error\n");
            exit(1);
        }

        printf("%d: received ping\n",getpid());

        if(write(pipe2_c2p[1],buffer,length) != length){
            printf("child--piepe-->parent error\n");
            exit(1);
        }
        exit(0);
    }
    
    //parent
    close(pipe1_p2c[0]);
    close(pipe2_c2p[1]);

    if(write(pipe1_p2c[1],buffer,length) != length){
        printf("parent--pipe-->child error\n");
        exit(1);
    }

    if(read(pipe2_c2p[0], buffer, length) != length){
        printf("child--pipe-->parent error\n");
        exit(1);
    }

    printf("%d: received pong\n",getpid());

    exit(0);
}

```

执行测试

```bash
$./grade-lab-util pingpong
```



### Lec2 C & GDB

------





### Lec3 OS组织和系统调用

------





### Lec4 页表

------

