### Test

* 使用dlopen,dlsym 不include ".h"
* include ".h" 动态链接
* include ".h" 一起编译

| make方式                        | dwarfdump结果          |
| ------------------------------- | ---------------------- |
| 使用dlopen,dlsym 不include ".h" | 没有loop.c的debug_line |
| include ".h" 动态链接           | 没有loop.c的debug_line |
| include ".h" 一起编译           | 有loop.c的debug_line   |

* 后续可以debug是否因为开始执行后才能读入相应的info,因为确实可以get相应的符号表
  ```
  (gdb) info sharedlibrary 
  From                To                  Syms Read   Shared Object Library
  0x00007ffff7fd0100  0x00007ffff7ff2684  Yes         /lib64/ld-linux-x86-64.so.2
  0x00007ffff7fac220  0x00007ffff7fad179  Yes         /lib/x86_64-linux-gnu/libdl.so.2
  0x00007ffff7f8eae0  0x00007ffff7f9e535  Yes         /lib/x86_64-linux-gnu/libpthread.so.0
  0x00007ffff7db8630  0x00007ffff7f2d27d  Yes         /lib/x86_64-linux-gnu/libc.so.6
  0x00007ffff7fc50a0  0x00007ffff7fc519e  Yes         ./libmylib.so
  ```

### 有关Debugger

* 对于所有的断点的设置，都需要对照`.debug_info`和`.debug_lines`,把文件的行号和变量,函数及其相关信息(内存地址范围等)对应起来,才可以达到断点的效果

### 解决方法

* 生成动态库-g

  ```cmake
  add_library(mylib SHARED mylib.c)
  target_compile_options(mylib PUBLIC -fPIC -g)
  ```

* 两种debug方式

  1. gdb ./main

     ```
     在load的代码处打断点,运行到相应位置后,即可在链接库中添加断点
     ```

  2. ./main 然后 gdb attach pid

     ```
     (gdb) cd /home/start/ST_CPP/ # 切换到工作目录
     Working directory /home/start/ST_CPP.
     (gdb) b mylib.c:11
     Breakpoint 1 at 0x7f8ab047e18e: file /home/start/ST_CPP/mylib.c, line 11.
     (gdb) c
     Continuing.
     [Switching to Thread 0x7f8ab024b700 (LWP 29354)]
     
     Thread 2 "main" hit Breakpoint 1, run () at /home/start/ST_CPP/mylib.c:11
     11	        ans++;
     (gdb) n
     12	        sleep(1);
     (gdb) n
     10	        printf("ans is %d\n", ans);
     (gdb) n
     
     Thread 2 "main" hit Breakpoint 1, run () at /home/start/ST_CPP/mylib.c:11
     11	        ans++;
     ```

     
