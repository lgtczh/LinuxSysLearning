#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>

#define ERR_EXIT(m) \
    do { \
        perror(m); \
        exit(EXIT_FAILURE); \
    } while(0)

int main(int argc, char *argv[])
{
    int pipefd[2];
    if (pipe(pipefd) == -1)
        ERR_EXIT("pipe");

    int flags = fcntl(pipefd[1], F_GETFL);
    fcntl(pipefd[1], F_SETFL, flags | O_NONBLOCK);
    int count = 0;
    while(1){
        int ret = write(pipefd[1], "A", 1);
        if (ret == -1)
            break;
        ++count;
    }
    printf("The size of pipe is %d\n", count);
    return 0;
}
