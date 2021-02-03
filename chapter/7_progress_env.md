# 进程环境

## 进程相关

1.C程序总是从`main`函数开始执行的。`main`函数的原型是：
```
    int main(int argc, char * argv[])
```
- 参数:
    - `argc`: 命令行参数的数目
    - `argv`: 由指向各命令行参数的指针所组成的数组。`ISO
      C`和`POSIX.1`都要求`argv[argc]`是一个空指针。

