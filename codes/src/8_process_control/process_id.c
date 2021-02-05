/*
 *  第八章：进程控制
 *
 *  测试 getpid 函数、gitppid 函数... 等进程 ID 相关函数的用法
 *
 */

#include "process_id.h"
#include "../header.h"
#include <unistd.h>
#include <stdio.h>

void print_pid()
{
    printf("process id: %d\n", getpid());
}

void print_parent_pid()
{
    printf("parent process id: %d\n", getppid());
}

void print_uid()
{
    printf("user process id: %d\n", getuid());
}

void print_euid()
{
    printf("efficient process id: %d\n", geteuid());
}

void print_gid()
{
  printf("group process id: %d\n",getgid());
}
void print_egid()
{
    printf("efficient group process id: %d\n",getegid());
}

void test_process_id()
{
    M_TRACE("---------  Begin test_process_id()  ---------\n");
    printf("process ids:\n");
    print_pid();
    print_parent_pid();
    print_uid();
    print_euid();
    print_gid();
    print_egid();
    M_TRACE("---------  End test_process_id()  ---------\n\n");
}
