/*
 * main 源文件
 */

#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include "src/header.h"
#include "src/7_process_enviroment/exit_atexit.h"
#include "src/7_process_enviroment/malloc_realloc.h"

int main(void)
{

    //******第七章******//
    //test_exit_atexit();
    test_malloc_realloc();
    return 0;
}
