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
    fd = open("hole.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1)
    {
        ERR_EXIT("open error");
    }
    
    write(fd, "ABCDE", 5);

    int ret = lseek(fd, 1024, SEEK_CUR);
    if (ret == -1)
        ERR_EXIT("lseek error");

    write(fd, "FG", 2);

    close(fd);    
    return 0;
}

