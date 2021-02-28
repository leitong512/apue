/*
 *   第十章：信号
 *
 * 测试 kill 函数、raise 函数的用法
 *
 */

#include "./kill_raise.h"
#include "../header.h"
#include <signal.h>

typedef void Handler_Func (int signo, siginfo_t *info, void *context);
extern void add_sigaction(int signo, sigset_t *set, int no_deffer, int restart, 
        Handler_Func handler);

/*
 *  \brief sig_print ：信号处理函数
 *  \param signo :
 *
 */
