/*
 *      第八章 进程控制
 *
 *  测试 wait 函数、 waitpid 函数
 *
 */

#ifndef WAIT_WAITPID
#define WAIT_WAITPID

#include <unistd.h>

/*
 *\brief My_wait ：包装了 wait 函数
 *\param staloc : 传递给 wait 函数的 staloc 函数
 *\return : 返回 wait 函数的值
 */

pid_t My_wait(int *staloc);


pid_t My_waitpid(pid_t pid, int *staloc, int options);

void print_return_status(int staloc);

void check_wait();

void check_waitpid();

void check_waitpid_signal();

pid_t child_exit(int fd, int exit_code);

pid_t child_abort(int fd);

pid_t child_signal(int fd);

void test_wait_waitpid();
