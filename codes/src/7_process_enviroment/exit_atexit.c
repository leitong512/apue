/*
 *  第七章：进程环境
 *
 *  测试 exit 函数、_Exit 函数、_exit 函数
 *
 */

#include "exit_atexit.h"
#include "../header.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

/*!
 *\brief f_1 : 终止处理程序 exit handler
 */

static void f_1()
{
    printf("f_1 is called\n");
}

/*
 *\brief f_2 : 终止处理程序 exit handler
 */

static void f_2()
{
    static int i = 0;
    i++;
    printf("f_2 is called, i = %d\n", i);
}


/*!
 *\brief f_3 : 终止处理程序 exit handler
 */

static void f_3()
{
    printf("f_3 is called\n");
}

void add_atexit() 
{
    if(atexit(f_1) != 0 )
    {
        printf("atexit (f_1) failed, because %s\n", strerror(errno));
    }
    if(atexit(f_2) != 0 )
    {
        printf("first atexit (f_2) failed, because %s\n", strerror(errno));
    }
    if(atexit(f_2) != 0 )
    {
        printf("second atexit (f_2) failed, because %s\n", strerror(errno));
    }
    if(atexit(f_3) != 0 )
    {
        printf("atexit (f_3) failed, because %s\n", strerror(errno));
    }
}

void test_exit_atexit()
{
    M_TRACE("--------- Begin test_exit_atexit() ---------\n");
    add_atexit();
    exit(259);
    //_Exit(269);
    //_exit(265);
    M_TRACE("--------- End test_exit_atexit() ----------\n");
}
