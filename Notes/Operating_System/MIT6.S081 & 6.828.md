

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



##### 利用管道与多进程打印质数

参考资料：[CSP Threads](https://swtch.com/~rsc/thread/) ，[CSDN](https://blog.csdn.net/zhayujie5200/article/details/106600925?utm_medium=distribute.pc_relevant.none-task-blog-baidujs_title-2&spm=1001.2101.3001.4242)

primes的功能是输出2~35之间的素数，实现方式是递归fork进程并使用管道链接，形成一条pipeline来对素数进行过滤。

每个进程收到的第一个数p一定是素数，后续的数如果能被p整除则之间丢弃，如果不能则输出到下一个进程，详细介绍可参考文档。伪代码如下：

```c
void primes() {
  p = read from left   // 从左边接收到的第一个数一定是素数
  if (fork() == 0): 
    primes()           // 子进程，进入递归
  else: 
    loop: 
      n = read from left  // 父进程，循环接收左边的输入  
      if (p % n != 0): 
        write n to right  // 不能被p整除则向右输出   
}
```

<div align=center>
    <img src="pic/sieve.gif" width="70%"/>
</div>

还需要注意两点：

- 文件描述符溢出： xv6限制fd的范围为0~15，而每次pipe()都会创建两个新的fd，如果不及时关闭不需要的fd，会导致文件描述符资源用尽。这里使用重定向到标准I/O的方式来避免生成新的fd，首先close()关闭标准I/O的fd，然后使用dup()复制所需的管道fd（会自动复制到序号最小的fd，即关闭的标准I/O），随后对pipe两侧fd进行关闭（此时只会移除描述符，不会关闭实际的file对象）。

- pipeline关闭： 在完成素数输出后，需要依次退出pipeline上的所有进程。在退出父进程前关闭其标准输入fd，此时read()将读取到eof（值为0），此时同样关闭子进程的标准输入fd，退出进程，这样进程链上的所有进程就可以退出。

源码

```c++
#include "kernel/types.h"
#include "user/user.h"

void func(int *input, int length){
    if(length == 1){             //递归基
        printf("prime %d\n",*input);
        return;
    }

    int p[2];
    int prime = *input;
    int temp;

    printf("prime %d\n",*input);//管道左侧（先进先出）第一个值一定是prime number
    pipe(p);
    
    int i;
    if(fork() == 0){            //子进程
        for(i = 0; i < length; ++i){
            temp = *(input + i);
            write(p[1], (char*)(&temp), 4);//往管道写入数据
        }
        exit(0);
    }
    close(p[1]); //重要

    if(fork() == 0){           //子进程
        int temp_length = 0;
        char temp_buffer[4];
        int temp_value;
        while(read(p[0],temp_buffer,4) != 0){ //读取管道数据
            temp_value = *((int *)temp_buffer);
            if(temp_value % prime != 0){      //不能被当前质数整除继续
                *input = temp_value;          //按顺序写入数组，覆盖原来的数据
                input += 1;
                temp_length ++;
            }//操作完成后，能被当前的质数整除的数字被抛弃，数据长度变短
        }
        func(input - temp_length, temp_length);//由于使用的是指针，将指针回退到数组首地址，递归
        exit(0);
    }

	wait(0);
	wait(0);
}

int main(){
    int input[34];
	int i = 0;
	for(; i < 34; i++){
		input[i] = i+2;
	}
	func(input, 34);
    exit(0);
}

```

```bash
xv6 kernel is booting

hart 1 starting
hart 2 starting
init: starting sh
$ primes
prime 2
prime 3
prime 5
prime 7
prime 11
prime 13
prime 17
prime 19
prime 23
prime 29
prime 31
$ QEMU: Terminated
root@ubuntu:~/Myfile/mitos/xv6-labs-2020# ./grade-lab-util primes
make: 'kernel/kernel' is up to date.
== Test primes == primes: OK (1.5s) 
    (Old xv6.out.primes failure log removed)
```

### Lec2 C & GDB

------





### Lec3 OS组织和系统调用

------





### Lec4 页表

------

