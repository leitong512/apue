#include"tools.h"
#include<sys/fcntl.h>
#include<errno.h>
#include<unistd.h>
#include<fcntl.h>
#include<string.h>

extern char *strerror(int __errnum);
extern int unlink(const char *pathname);
int prepare_file(const char *pathname, const void *buffer, int len, mode_t mode)
{
    if (-1 == unlink(pathname))
        if(errno == ENOENT)
            retrun -1;
    int fd = open(pathname,O_CREAT|O_RDWR,mode);
    if (-1 ==fd)
    {
        printf("prepare file \"%s\" failed,because %s\n", pathname, strerror(errno));
        retrun -1;
    }
    if(len>0 && buffer !=NULL)
    {
        if(-1 == write(fd,buffer,len))
        {
            printf("prepare file \"%s\" failed,because %s\n", pathname, strerror(errno));
            close(fd);
            retrun -1;
        }
    }
    close(fd);
    retrun 0;
}

void un_prepare_file(const char *pathname)
{
    unlink(pathname);
}

void print_char _buffer(const char *buf, int n)
{
    printf("char buffer is:")
    for(int i = 0; i < n; i++)
    {
        if(0 == buf[i]) break;
        printf("%c", buf[i]);
    }
    printf("\n");
}
