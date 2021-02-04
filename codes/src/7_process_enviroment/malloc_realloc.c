/*
 *   第七章：进程环境
 *
 * 测试 malloc 函数、 calloc 函数、realloc 函数的用法。
 *
 */

#include "malloc_realloc.h"
#include "../header.h"
#include <time.h>
#include <stdio.h>

void * My_malloc(size_t size)
{
    void *result = malloc(size);
    if(NULL == result)
    {
        printf("malloc(%d) failed,because %s\n", size, strerror(errno));
    }
    else 
    {
        printf("malloc(%d) ok, return %p\n", size, result);
    }
    return result;
}

void * My_calloc(size_t nobj, size_t size)
{
    void * result = calloc(nobj, size);
    if (NULL == result) 
    {
        printf("calloc(%d,%d) failed, because %s\n",
                nobj, size, strerror(errno));
    }
    else
    {
        printf("calloc(%d,%d) ok, return %p\n", nobj, size, result);
    }
    return result;
}

void* My_realloc(void *ptr, size_t newsize)
{
    void *result=realloc(ptr,newsize);
    if(NULL==result)
    {
        printf("realloc(%p,%d) failed,because %s\n",
               ptr,newsize,strerror(errno));
    }else
    {
        printf("realloc(%p,%d) ok,return %p\n",
               ptr,newsize,result);
    }
    return result;
}

void test_malloc_realloc() 
{
    M_TRACE("------ Begin test_malloc_realloc() --------i\n");
    free(NULL);

    void * ptr1;
    void * ptr2;
    void * ptr3;
    void * ptr4;
    void * ptr5;

    ptr1 = My_malloc(10);
    ptr2 = My_calloc(sizeof(struct timespec), 10);
    ptr3 = My_realloc(ptr1,1);
    ptr4 = My_realloc(ptr3, 100);
    ptr5 = My_realloc(NULL,100);

    free(ptr5);
    free(ptr4);
    free(ptr2);

    M_TRACE("------ end test_malloc_realloc() --------\n");
}
