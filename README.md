## README

### 介绍

本项目对`dlopen`打开动态链接库同时使用GDB进行debug的可行性进行测试

* 生成动态链接库并在`main.c`中调用
* 调用方式为,通过`dlopen`和`dlsym`读取动态链接库`libmylib.so`中的函数`run()`(此函数从0开始计数,每`1s`加一并输出当前计数的值,为方便测试未设置退出条件)
* 测试结果分析位于`./doc/result.md`

### Build

```shell
cmake .
make
```

### 测试方式

对如下两种debug方式进行测试,下述步骤均需要进入`build`目录后进行

* `gdb ./main`,添加断点后`run`,步骤如下

  * 在`main.c`第26行,也就是调用动态库中函数前添加断点
  * `run`运行
  * 在`mylib.c`中的第11行也就是计数器自增的那一行,添加断点
  * 进行调试,结果如下

  ```shell
  (gdb) b main.c:26
  Breakpoint 1 at 0x937: file /home/start_0916/gdb-debug/src/main.c, line 26.
  (gdb) run 
  Starting program: /home/start_0916/gdb-debug/build/main 
  [Thread debugging using libthread_db enabled]
  Using host libthread_db library "/lib/x86_64-linux-gnu/libthread_db.so.1".
  
  Breakpoint 1, main () at /home/start_0916/gdb-debug/src/main.c:26
  26          int rc = pthread_create(&thread, NULL, run, NULL);
  (gdb) b mylib.c:11
  Breakpoint 2 at 0x7ffff73bd6df: file /home/start_0916/gdb-debug/src/mylib.c, line 11.
  (gdb) c
  Continuing.
  [New Thread 0x7ffff73bc700 (LWP 1249)]
  func run
  ans is 0
  [Switching to Thread 0x7ffff73bc700 (LWP 1249)]
  
  Thread 2 "main" hit Breakpoint 2, run (arg=0x0) at /home/start_0916/gdb-debug/src/mylib.c:11
  11              ans++;
  (gdb) c
  Continuing.
  ans is 1
  
  Thread 2 "main" hit Breakpoint 2, run (arg=0x0) at /home/start_0916/gdb-debug/src/mylib.c:11
  11              ans++;
  (gdb) info breakpoints 
  Num     Type           Disp Enb Address            What
  1       breakpoint     keep y   0x0000555555554937 in main at /home/start_0916/gdb-debug/src/main.c:26
          breakpoint already hit 1 time
  2       breakpoint     keep y   0x00007ffff73bd6df in run at /home/start_0916/gdb-debug/src/mylib.c:11
          breakpoint already hit 2 times
  ```
* `./main`开始运行,随后获取进程`PID`,然后`gdb attach ${PID}`

  然后在`mylib.c`中的第11行也就是计数器自增的那一行,添加断点并调试,结果如下

  ```shell
  (gdb) b mylib.c:11
  Breakpoint 1 at 0x7f8943c356df: file /home/start_0916/gdb-debug/src/mylib.c, line 11.
  (gdb) c
  Continuing.
  [Switching to Thread 0x7f8943c34700 (LWP 30719)]
  
  Thread 2 "main" hit Breakpoint 1, run (arg=0x0) at /home/start_0916/gdb-debug/src/mylib.c:11
  11	        ans++;
  (gdb) c
  Continuing.
  
  Thread 2 "main" hit Breakpoint 1, run (arg=0x0) at /home/start_0916/gdb-debug/src/mylib.c:11
  11	        ans++;
  (gdb) c
  Continuing.
  
  Thread 2 "main" hit Breakpoint 1, run (arg=0x0) at /home/start_0916/gdb-debug/src/mylib.c:11
  11	        ans++;
  (gdb) info breakpoints 
  Num     Type           Disp Enb Address            What
  1       breakpoint     keep y   0x00007f8943c356df in run at /home/start_0916/gdb-debug/src/mylib.c:11
  	breakpoint already hit 3 times
  ```

### Tips

如果在gdb attach的时候报错,可以参考如下指令

```
sudo sysctl -w kernel.yama.ptrace_scope=0
```

其默认值为1,查看文件`/etc/sysctl.d/10-ptrace.conf`可知

>A PTRACE scope of "0" is the more permissive mode.
>
>A scope of "1" limits PTRACE only to direct child processes (e.g. "gdb name-of-program" and
>
>"strace -f name-of-program" work, but gdb's "attach" and "strace -fp $PID" do not).

因此可以修改为0
