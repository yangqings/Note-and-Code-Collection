## CLion软件使用（Windows环境）

工具链选择GCC



### 步骤 1

下载工具链，[MinGW](https://sourceforge.net/projects/mingw-w64/files/)是GNU最小集成开发工具包

#### MinGW-W64 Online Installer

- [MinGW-W64-install.exe](https://sourceforge.net/projects/mingw-w64/files/Toolchains targetting Win32/Personal Builds/mingw-builds/installer/mingw-w64-install.exe)

#### MinGW-W64 GCC-8.1.0

- [x86_64-posix-sjlj](https://sourceforge.net/projects/mingw-w64/files/Toolchains targetting Win64/Personal Builds/mingw-builds/8.1.0/threads-posix/sjlj/x86_64-8.1.0-release-posix-sjlj-rt_v6-rev0.7z)
- [x86_64-posix-seh](https://sourceforge.net/projects/mingw-w64/files/Toolchains targetting Win64/Personal Builds/mingw-builds/8.1.0/threads-posix/seh/x86_64-8.1.0-release-posix-seh-rt_v6-rev0.7z)
- [x86_64-win32-sjlj](https://sourceforge.net/projects/mingw-w64/files/Toolchains targetting Win64/Personal Builds/mingw-builds/8.1.0/threads-win32/sjlj/x86_64-8.1.0-release-win32-sjlj-rt_v6-rev0.7z)
- [x86_64-win32-seh](https://sourceforge.net/projects/mingw-w64/files/Toolchains targetting Win64/Personal Builds/mingw-builds/8.1.0/threads-win32/seh/x86_64-8.1.0-release-win32-seh-rt_v6-rev0.7z)
- [i686-posix-sjlj](https://sourceforge.net/projects/mingw-w64/files/Toolchains targetting Win32/Personal Builds/mingw-builds/8.1.0/threads-posix/sjlj/i686-8.1.0-release-posix-sjlj-rt_v6-rev0.7z)
- [i686-posix-dwarf](https://sourceforge.net/projects/mingw-w64/files/Toolchains targetting Win32/Personal Builds/mingw-builds/8.1.0/threads-posix/dwarf/i686-8.1.0-release-posix-dwarf-rt_v6-rev0.7z)
- [i686-win32-sjlj](https://sourceforge.net/projects/mingw-w64/files/Toolchains targetting Win32/Personal Builds/mingw-builds/8.1.0/threads-win32/sjlj/i686-8.1.0-release-win32-sjlj-rt_v6-rev0.7z)
- [i686-win32-dwarf](https://sourceforge.net/projects/mingw-w64/files/Toolchains targetting Win32/Personal Builds/mingw-builds/8.1.0/threads-win32/dwarf/i686-8.1.0-release-win32-dwarf-rt_v6-rev0.7z)

不要下载exe，因为需要翻墙，exe无法下载。

几个版本的区别：

#### 释义1：

- DWARF：一种带调试信息(DWARF- 2（DW2）EH)的包, 所以比一般的包尺寸大，仅支持32位系统
- SJLJ：跨平台，支持32，64位系统，缺点是：运行速度稍慢，GCC不支持
- SEH: 调用系统机制处理异常，支持32，64位系统，缺点是：Gcc不支持（即将支持）

#### 释义2：

- x86_64: 简称X64，64位操作系统
- i686: 32位操作系统 (i386的子集)，差不多奔腾2(1997年5月)之后的CPU都是可以用的；

#### 释义3：

- posix: 启用了C++ 11 多线程特性
- win32: 未启用 （从时间线上正在尝试也启用部分 Treading）

#### 区别

- DWARF DWARF- 2（DW2）EH ，这需要使用DWARF-2（或DWARF-3）调试信息。 DW-2 EH可以导致可执行文件略显膨胀，因为大的调用堆栈解开表必须包含在可执行文件中。
- setjmp / longjmp（SJLJ）。基于SJLJ的EH比DW2 EH慢得多（在没有异常时会惩罚甚至正常执行），但是可以在没有使用GCC编译的代码或没有调用堆栈的代码上工作。
- 结构化异常处理（SEH） （Structured Exception Handling）Windows使用自己的异常处理机制。



### 步骤 2 

解压到某个盘的根目录，不能有中文路径

打开系统信息，高级设计添加环境变量，PATH，把`\mingw64\bin`和`\mingw64\x86_64-w64-mingw32\bin`



### 步骤 3

CLion的setting选项中的toolchains添加编译器和make工具的路径

