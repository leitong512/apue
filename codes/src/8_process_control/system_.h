/* 
 *  第八章 进程环境
 *
 *  测试 system 函数的参数
 *
 */

#ifndef SYSTEM_
#define SYSTEM_

/*
 *  \brief My_system : 包装了 system 函数
 *  \param cmdstring : 传递给 system 函数的参数
 *  \return : 返回 system 函数的值
 */
int My_system(const char *cmdstring);

/*!
 *  \brief test_system : 测试 system 函数的用法
 */
void test_system();

#endif
