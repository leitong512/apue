/*
 *  第八章：进程控制
 *
 *  测试 fork 函数的用法
 */
#include "fork.h"
#include "../header.h"
#include "../tools.h"
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

extern int My_open(const char *path, int oflag);
extern int print_pid();
extern int print_parent_pid();



int My_open(const char *path, int oflag)
{
    int result=open(path,oflag);
    if(-1==result)
        printf("open(\"%s\",%d) failed,because %s\n",path,oflag,strerror(errno));
    else
        printf("open(\"%s\",%d) return file descriptor %d\n",path,oflag,result);
    return result;
}
/*
 * \brief process_func :完成每个进程中的主要工作
 * \param fd : 打开文件描述符，用于记录锁
 * \param append_str : 说明每个进程的字符串
 */
static void process_func(int fd, const char *append_str)
{
    fcntl_lock(fd);  //加锁
    printf("%s\n", append_str);
    print_pid();
    print_parent_pid();
    printf("%s\n",append_str);
    fcntl_unlock(fd); //解锁
}

void test_fork()
{
    M_TRACE("-------- Begin test_fork() ----------\n");
    assert(prepare_file("test", "abc", 3, S_IRWXU) == 0);
    int fd = My_open("test", O_RDWR);
    if ( -1 == fd )
    {
        un_prepare_file("test");
        M_TRACE("-------- End test_fork() --------\n\n");
        return ;
    }
    //**********打开文件成功***********/
    pid_t id = fork();
    if( 0 == id )
    {
        //child 1 
        process_func(fd, "**********In child 1**********");
        _exit(0);
    }
    sleep(2);  //确保父进程在子进程之后执行
    id = fork();
    printf("this is in the second fork\n");
    if (0 == id)
    {
        //child 2
        process_func(fd, "*********In child 2*********");
        _exit(0);
    }
    sleep(2);
    process_func(fd,"**********In parent*********");
    close(fd);
    un_prepare_file("test");
    M_TRACE("-------- End test_fork() ----------\n\n");
}
