#ifndef TOOLS
#define TOOLS
#include<sys/types.h>
#include<time.h>

/*!
 * \brief: prepare_file :
 * 为测试准备条件：新建一个文件(若存在则先删除之),然后向文件写入内容
 * \param: pathname:新建文件的路径名
 * \param: buffer:待写入文件的内容缓存
 * \param: len: 待写入文件的内容的长度
 * \param: mode: 新建文件的权限
 */
int prepare_file(const char*pathname, const void *buffer,int len, mode_t mode);


/*
 *\brief: un_prepare_file:清理测试准备文件：删除新建的文件
 *\param: pathname:新建的文件的路径名
 */
void un_prepare_file(const char *pathname);

/*
 *\brief: print_char_buffer 打印字符数组的内容
 *\param: buf 字符数组地址
 *\param: n 数组长度
 */

void print_char buffer(const char *buf, int n);
