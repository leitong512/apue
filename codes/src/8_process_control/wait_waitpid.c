/*
 *      第八章 进程控制
 *
 *  测试 wait 函数、 waitpid 函数的用法
 *
 */

#include "wait_waitpid.h"
#include "../header.h"
#include "../tools.h"
#include <sys/wait.h>
#include <fcntl.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

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
 *  \brief process_func ：完成每个进程的主要工作
 *  \param fd : 打开的文件描述符，用于记录锁
 *  \param append_str : 说明每个进程的字符串
 */
static void process_func(int fd, const char* append_str)
{
    fcntl_lock(fd);
    printf("%s\n", append_str);
    print_pid();
    print_parent_pid();
    printf("%s\n", append_str);
    fcntl_unlock(fd);
}

pid_t My_wait(int *staloc)
{
    pid_t result = wait(staloc);
    if (result <= 0)
    {
        printf("wait(%p) failed, because %s\n", staloc, strerror(errno));
    }
    else 
    {
        printf("wait(%p) ok, process<pid = %d> terminated.", staloc, result);
        if(NULL == staloc)
        {
            printf("\n");
        }
        else 
        {
            print_return_status(*staloc);
        }
    }
    return result;
}

pid_t My_waitpid(pid_t pid, int *staloc, int options)
{
    pid_t result = waitpid(pid, staloc, options);
    if (result <= 0)
    {
        printf("waitpid(%d, %p, %d) failed ,because %s \n", 
                pid, staloc, options, strerror(errno));
    }
    else 
    {
        printf("waitpid(%d, %p, %d) ok, process<pid = %d> terminated.",
                pid, staloc, options, result);
        if (NULL == staloc)
        {
            printf("\n");
        }
        else 
        {
            print_return_status(*staloc);
        }
    }
    return result;
}

void print_return_status(int staloc)
{
    if(WIFEXITED(staloc))
    {
        printf("return status:exit normally, exit code is %d\n", 
                WEXITSTATUS(staloc));
    }
    if( WIFSIGNALED(staloc))
    {
        printf("return status:terminate by signal, signal no is %d\n", 
                WTERMSIG(staloc));
    }
}

void check_wait()
{
    int status;
    int child_id;
    while((child_id = My_wait(&status)) > 0) //wait 失败返回
    {
        ;
    }
}

void check_waitpid()
{
    int status;
    int child_id;
    //等待所有子进程；阻塞式，一定不能指定WNOHANG
    while( (child_id = My_waitpid(-1, &status, 0)) > 0)
    {
        ;
    }
}

void check_waitpid_signal()
{
    int status;
    int child_id;
    //等待所有子进程，阻塞式，一定不能指定WNOHANG
    while( (child_id = My_waitpid(-1, &status,0)) > 0 
            || (child_id <= 0 || errno == EINTR) )
    {
        ;
    }
}

pid_t child_exit(int fd, int exit_code)
{
    pid_t pid = fork();
    if( 0 == pid )
    {
        process_func(fd, "**********Child_exit***********");
        _exit(exit_code);
        printf("never reached\n");
        return 0;
    }
    return pid;
}

pid_t child_abort(int fd)
{
    pid_t pid = fork();
    if (0 == pid)
    {
        process_func(fd, "*********Child_abort**********");
        abort();
        printf("never reached\n");
        return 0;
    }
    return pid;
}

pid_t child_signal(int fd)
{
    pid_t pid = fork();
    if ( 0 == pid )
    {
        process_func(fd, "**********Child_signal*********");
        kill(getpid(), SIGKILL); //向自己发送 SIGKILL信号
        sleep(3); //确保信号处理程序能执行完毕
        return 0;
    }
    return pid;
}

void test_wait_waitpid()
{
    M_TRACE("--------- Begin test_wait_waitpid() -----------\n");
    assert(prepare_file("test", "abc", 3, S_IRWXU) == 0);
    int fd = My_open("test", O_RDWR);
    if( -1 == fd )
    {
        un_prepare_file("test");
        M_TRACE("--------End test_fork() ------------\n\n");
        return ;
    }

    //打开文件成功
    process_func(fd, "***************Parent************");
    if( 0 != child_exit(fd, 100) )
    {
        //parent
        sleep(1);  //确保父进程稍后执行
        if ( 0 != child_abort(fd) )
        {
            //parent
            sleep(1);  //确保父进程稍后执行
            if ( 0 != child_signal(fd) )
            {
                //parent
                sleep(1);//确保父进程稍后执行
                check_wait();  //only wait at parent 
                //check_waitpid(); //only wait at parent
                
                close(fd);
                un_prepare_file("test");
                M_TRACE("---------- End test_wait_waitpid() ---------\n\n");
            }

        }
    }
}
