### Test

* 使用dlopen,dlsym 不include ".h"
* include ".h" 动态链接
* include ".h" 一起编译

| make方式                        | dwarfdump结果          |
| ------------------------------- | ---------------------- |
| 使用dlopen,dlsym 不include ".h" | 没有loop.c的debug_line |
| include ".h" 动态链接           | 没有loop.c的debug_line |
| include ".h" 一起编译           | 有loop.c的debug_line   |

