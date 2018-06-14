#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

#define ERR_EXIT(m) \
    do { \
        perror(m); \
        exit(EXIT_FAILURE); \
    } while(0)

int main(int argc, char *argv[])
{
    if (argc < 2)
        fprintf(stderr, "./10fifor <filename>\n");

    char *fifoName = "tp";
    
    // 以创建和只写的方式打开要拷贝的文件
    int fd = open(argv[1], O_WRONLY | O_CREAT, 0644);
    if (fd == -1)
        ERR_EXIT("open file");

    // 以只读的方式打开通道
    int outFifo = open(fifoName, O_RDONLY);
    if (outFifo == -1)
        ERR_EXIT("open outFifo");

    char buf[1024];
    int n;
    while( (n = read(outFifo, buf, 1024)) > 0){
        write(fd, buf, n);
    }
    
    close(fd);
    close(outFifo); 
    return 0;
}
