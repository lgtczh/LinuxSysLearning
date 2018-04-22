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

int main(int argc, char *argv[])
{
    int infd, outfd;
    if (argc != 3){
        fprintf(stderr, "Usage %s src dest\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    
    infd = open(argv[1], O_RDONLY);
    if (infd == -1)
    {
        ERR_EXIT("open src error");
    }
    
    if ((outfd = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0644)) == -1){
        ERR_EXIT("open dest error");
    }

    char buf[1024];
    int nread;
    while(1){
        if ((nread = read(infd, buf, sizeof(buf))) < 0){
            ERR_EXIT("read error");
        }else if (nread > 0) {
            if (write(outfd, buf, nread) < 0)
                ERR_EXIT("write error");
        }else{
            break;
        }
    }
    
    close(infd);
    close(outfd);
    return 0;
}

