/*
 *  第八章：进程控制
 *
 *  测试 getpid 函数、getppid 函数... 等进程 ID 相关函数的用法
 *
 */

#ifndef PROCESS_ID
#define PROCESS_ID

/*!
 * \brief print_pid : 打印进程 id
 */
void print_pid();
/*!
 * \brief print_parent_pid : 打印进程的父进程 id
 */
void print_parent_pid();
/*!
 * \brief print_uid  : 打印进程的用户 id
 */
void print_uid();
/*!
 * \brief print_euid : 打印进程的有效用户 id
 */
void print_euid();
/*!
 * \brief print_gid : 打印进程的组 id
 */
void print_gid();
/*!
 * \brief print_egid : 打印进程的有效组 id
 */
void print_egid();
/*!
 * \brief test_progress_id : 测试 getpid 函数、 getppid 函数... 等进程 ID 相关函数
 */
void test_process_id();
#endif // PROCESS_ID
