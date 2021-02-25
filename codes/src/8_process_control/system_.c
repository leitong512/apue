/*
 *  第八章 进程环境
 *
 *  测试 system 函数用法
 *
 */

#include"system_.h"
#include"../header.h"
#include <stdlib.h>
#include <stdio.h>

extern void print_return_status(int staloc);

int My_system( const char *cmdstring )
{
    int result = system(cmdstring);
    if(-1 == result)
    {
        printf("system(\"%s\") failed,because fork error or waitpid error :(%s)\n",
               cmdstring,strerror(errno));
    } else if (WIFEXITED(result) && 127 == WEXITSTATUS(result))
    {
        printf("system(\"%s\") failed,because shell can not run cmdstring\n",
               cmdstring);
        print_return_status(result);
    } else {
        printf("system(\"%s\")  ok\n",cmdstring);
        print_return_status(result);
    }
    return result;
}

void test_system(){
    M_TRACE("---------  Begin test_system()  ---------\n");
    My_system("netstat -na | grep 6379"); //命令存在
    My_system("aaaa"); // 不存在命令
    M_TRACE("---------  End test_system()  ---------\n\n");
}
