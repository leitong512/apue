#include"tools.h"
#include<sys/fcntl.h>
#include<errno.h>
#include<unistd.h>
#include<fcntl.h>
#include<string.h>
#include <stdio.h>

extern char *strerror(int __errnum);
extern int unlink(const char *pathname);
int prepare_file(const char *pathname, const void *buffer, int len, mode_t mode)
{
    if (-1 == unlink(pathname))
        if(errno != ENOENT)
            return -1;
    int fd = open(pathname,O_CREAT|O_RDWR,mode);
    if (-1 ==fd)
    {
        printf("prepare file \"%s\" failed,because %s\n", pathname, strerror(errno));
        return -1;
    }
    if(len>0 && buffer !=NULL)
    {
        if(-1 == write(fd,buffer,len))
        {
            printf("prepare file \"%s\" failed,because %s\n", pathname, strerror(errno));
            close(fd);
            return -1;
        }
    }
    close(fd);
    return 0;
}

void un_prepare_file(const char *pathname)
{
    unlink(pathname);
}

void print_char_buffer(const char *buf, int n)
{
    printf("char buffer is:");
    for(int i = 0; i < n; i++)
    {
        if(0 == buf[i]) break;
        printf("%c", buf[i]);
    }
    printf("\n");
}

void fcntl_lock(int fd)
{
    struct flock data;
    data.l_type=F_WRLCK;
    data.l_whence=SEEK_SET;
    data.l_start=0;
    data.l_len=0;
    int result = fcntl(fd, F_SETLKW, &data);
    if ( -1 == result )
    {
        printf("fcntl_lock failed, because %s\n", strerror(errno));
    }
}

void fcntl_unlock(int fd)
{
    struct flock data;
    data.l_type = F_UNLCK;
    data.l_whence = SEEK_SET;
    data.l_start = 0;
    data.l_len = 0;
    int result = fcntl(fd, F_SETLKW, &data);
    if ( -1 == result )
    {
        printf("fcntl_unlock failed, because %s\n", strerror(errno));
    }
}

char *abs_path(const char *dir_name, const char *file_name)
{
    static char buffer[1024];
    if(NULL == dir_name)
    {
        printf("dir_name must not be NULL\n");
        return NULL;
    }
    if(NULL == file_name)
    {
        printf("file_name must not be NULL\n");
        return NULL;
    }
    if(dir_name[0] != '/')
    {
        printf("file_name must start with '/'\n");
        return NULL;
    }
    if(file_name[0] == '/')
    {
        printf("file_name must not start with '/'");
        return NULL;
    }
    
    strcpy(buffer, dir_name);
    strcat(buffer,"/");
    strcat(buffer, file_name);
    return buffer;
}
