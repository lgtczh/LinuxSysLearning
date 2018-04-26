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
    int fd;
    fd = open("test.txt", O_WRONLY);
    if(fd == -1)
        ERR_EXIT("open error");

    close(1);
    if (fcntl(fd, F_DUPFD, 0) < 0)
        ERR_EXIT("dup fd error");
    printf("hello\n");
    return 0;
}

