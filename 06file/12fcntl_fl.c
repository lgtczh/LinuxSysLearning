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
    char buf[1024] = {0};
    int ret, flags;

    flags = fcntl(0, F_GETFL);
    if (flags == -1)
        ERR_EXIT("get flag error");

    ret = fcntl(0, F_SETFL, flags | O_NONBLOCK);
    if (ret == -1)
        ERR_EXIT("set flag error");

    if (read(0, buf, 1024) == -1)
        ERR_EXIT("read from stdin error");
    
    printf("from stdin get %s\n", buf);
 
    return 0;
}

