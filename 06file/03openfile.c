#include <unistd.h> //UNIX标准头文件
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>

#define ERR_EXIT(m)\
    do \
    { \
        perror(m); \
        exit(EXIT_FAILURE); \
    }while(0)

int main(void)
{
    umask(0202);
    int fd;
    fd = open("test.txt", O_WRONLY | O_CREAT, 0766);
    if (fd == -1)
    {
        ERR_EXIT("open error");
        /*
        fprintf(stderr, "open error with errno=%d,errInfo:%s\n", errno, strerror(errno));
        exit(EXIT_FAILURE);
        */
    }
    printf("open success!\n");
    return 0;
}

