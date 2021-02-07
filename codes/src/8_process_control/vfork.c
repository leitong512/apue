/*
 *  第八章：进程控制
 *
 *  测试 vfork 函数
 *
 */
#include"vfork.h"
#include"../header.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

extern void print_pid();
extern void print_parent_pid();

int My_open(const char *path, int oflag)
{
    int result=open(path,oflag);
    if(-1==result)
        printf("open(\"%s\",%d) failed,because %s\n",path,oflag,strerror(errno));
    else
        printf("open(\"%s\",%d) return file descriptor %d\n",path,oflag,result);
    return result;
}

void test_vfork()
{
    M_TRACE("---------- Begin test_vfork ---------\n");
    assert(prepare_file("test","abc", 3, S_IRWXU) == 0);
    int fd = My_open("test", O_RDWR);
    if( -1 == fd )
    {
        un_prepare_file("test");
        M_TRACE("---------- End test_vfork ---------\n");
        return ;
    }
    /*********打开文件成功***********/
    int i = 0;
    int id = vfork();
    if ( 0 == id )
    {
        //child
        sleep(2);
        fcntl_lock(fd);
        printf("********* In Child *********\n");
        print_pid();
        print_parent_pid();
        printf("i = %d\n",i);
        i = 999;
        printf("********* In Child *********\n");
        fcntl_unlock(fd);
        _exit(0);
    }
    else 
    {
        //parent
        fcntl_lock(fd);  // 加锁
        printf("*********** In Parent ***********\n");
        print_pid();
        print_parent_pid();
        printf("i=%d\n",i);
        printf("*********** In Parent ***********\n");
        fcntl_unlock(fd); // 解锁
    }
    close(fd);
    un_prepare_file("test");
    M_TRACE("---------- End test_vfork ---------\n");
}
