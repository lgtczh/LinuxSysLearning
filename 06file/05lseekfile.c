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
    fd = open("test.txt", O_RDONLY);
    if (fd == -1)
    {
        ERR_EXIT("open error");
    }

    int ret = lseek(fd, 5, SEEK_CUR);
    printf("current offset = %d\n", (int)ret);
    
    char buf[1024];
    if (read(fd, buf, 5) < 0)
        ERR_EXIT("read error");
    fprintf(stdout, "buf = %s\n", buf);
    return 0;
}

