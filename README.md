## README

### 介绍

本项目对`dlopen`动态链接库同时使用GDB进行debug的可行性进行测试

* 生成动态链接库并在`main.c`中调用
* 调用方式为,通过`dlopen`和`dlsym`读取动态链接库`libmylib.so`并获取函数`run()`(从0开始计数,每`1s`加一,为方便测试未设置退出条件)
* 测试结果位于`./doc/result.md`

### Build

```shell
cmake .
make
```

### 测试方式

对如下两种debug方式进行测试

* `gdb ./main`,添加断点后`run`
* `./main`,随后获取进程`PID`,然后`gdb attach ${PID}`

### Tips

如果在gdb attach的时候报错,可以参考如下指令

```
sudo sysctl -w kernel.yama.ptrace_scope=0
```

因为默认值为1,查看文件`/etc/sysctl.d/10-ptrace.conf`可知

>A PTRACE scope of "0" is the more permissive mode.
>
>A scope of "1" limits PTRACE only to direct child processes (e.g. "gdb name-of-program" and
>
>"strace -f name-of-program" work, but gdb's "attach" and "strace -fp $PID" do not).

因此可以修改为0.
