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
        fprintf(stderr, "./10fifo_w <filename>\n");

    char *fifoName = "tp";
    if (access(fifoName, F_OK) == 0){
        // file exist
        struct stat statbuf;
        if (stat(fifoName, &statbuf) == -1)
            ERR_EXIT("stat");
        if (!S_ISFIFO(statbuf.st_mode)){
            // file is no fifo
            rmdir(fifoName);
            mkfifo(fifoName, 0644);
        }
    }else
        mkfifo(fifoName, 0644);
    
    // 以只读的方式打开要拷贝的文件
    int fd = open(argv[1], O_RDONLY);
    if (fd == -1)
        ERR_EXIT("open file");

    // 以只写的方式打开通道
    int inputFifo = open(fifoName, O_WRONLY);
    if (inputFifo == -1)
        ERR_EXIT("open inputFifo");

    char buf[1024];
    int n;
    while( (n = read(fd, buf, 1024)) > 0){
        write(inputFifo, buf, n);
    }
    
    close(fd);
    close(inputFifo); 
    return 0;
}
