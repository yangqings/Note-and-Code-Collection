## Linux Operating System

[TOC]

### 0 概述

学习书籍

<div align=center>
    <img src="pic/Linux/0 Roadmap.jpeg" width="80%"/>
</div>



<div align=center>
    <img src="pic/Linux/2 操作系统内核体系结构图.jpeg" width="60%"/>
</div>
- 管道pipe

```shell
ps -ef | grep 关键字 | awk '{print $2}' | xargs kill -9
```

命名管道、匿名管道: 

这里面的竖线“|”就是一个管道。它会将前一个命令的输出，作为后一个命令的输入。从管道的这个名称可以看出来，管道是一种单向传输数据的机制，它其实是一段缓存，里面的数据只能从一端写入，从另一端读出。如果想互相通信，我们需要创建两个管道才行。管道分为两种类型，“|” 表示的管道称为匿名管道，意思就是这个类型的管道没有名字，用完了就销毁了。就像上面那个命令里面的一样，竖线代表的管道随着命令的执行自动创建、自动销毁。用户甚至都不知道自己在用管道这种技术，就已经解决了问题。所以这也是面试题里面经常会问的，到时候千万别说这是竖线，而要回答背后的机制，管道。

另外一种类型是命名管道。这个类型的管道需要通过 mkfifo 命令显式地创建。

- 消息队列
- 共享内存
- 信号量
- 信号

x86两种模式：

| X86两种模式 |                 区别                 |
| :---------: | :----------------------------------: |
|   实模式    | 只能寻址1M，每个段64KB，为了前向兼容 |
|  保护模式   |          32位系统可以寻址4G          |

部分汇编指令（X86）

- move a b : 把b值赋给a,使a=b
- call和ret : call调用子程序，子程序以ret结尾
- jmp : 无条件跳
- int : 中断指令
- add a b : 加法,a=a+b
- or : 或运算
- xor : 异或运算
- shl : 算术左移
- ahr : 算术右移
- push xxx : 压xxx入栈
- pop xxx: xxx出栈
- inc: 加1
- dec: 减1
- sub a b : a=a-b
- cmp: 减法比较，修改标志位


### 1 系统初始化

\- 实模式只有 1MB 内存寻址空间(X86)
\- 加电, 重置 CS 为 0xFFFF , IP 为 0x0000, 对应 BIOS 程序
\- 0xF0000-0xFFFFF 映射到 BIOS 程序(存储在ROM中), BIOS 做以下三件事:
  \- 检查硬件
  \- 提供基本输入(中断)输出(显存映射)服务
  \- 加载 MBR 到内存(0x7c00)
\- MRB: 启动盘第一个扇区(512B, 由 Grub2 写入 boot.img 镜像)
\- boot.img 加载 Grub2 的 core.img 镜像
\- core.img 包括 diskboot.img, lzma_decompress.img, kernel.img 以及其他模块
\- boot.img 先加载运行 diskroot.img, 再由 diskroot.img 加载 core.img 的其他内容
\- diskboot.img 解压运行 lzma_compress.img, 由lzma_compress.img 切换到保护模式

\-----------

\- 切换到保护模式需要做以下三件事:
  \- 启用分段, 辅助进程管理
  \- 启动分页, 辅助内存管理
  \- 打开其他地址线
  \- lzma_compress.img 解压运行 grub 内核 kernel.img, kernel.img 做以下四件事:
  \- 解析 grub.conf 文件
  \- 选择操作系统
  \- 例如选择 linux16, 会先读取内核头部数据进行检查, 检查通过后加载完整系统内核
  \- 启动系统内核

### 2 进程管理



### 3 内存管理



### 4 文件系统