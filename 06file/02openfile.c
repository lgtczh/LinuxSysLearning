#include <unistd.h> //UNIX标准头文件
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>

//宏不能有两条语句，所以通过()将它们放在一起
//#define ERR_EXIT(m) (perror(m), exit(EXIT_FAILURE))

//使用do-while语句, 通过"\"来实现换行,前面可以有空格，但后面不能有空格
#define ERR_EXIT(m)\
    do \
    { \
        perror(m); \
        exit(EXIT_FAILURE); \
    }while(0)

int main(void)
{
    int fd;
    fd = open("test.txt", O_RDONLY);
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

