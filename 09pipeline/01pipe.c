#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>


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

    pid_t pid;
    if ((pid = fork()) == -1)
        ERR_EXIT("fork");

    if (pid == 0){
        close(pipefd[0]);
        write(pipefd[1], "hello", 5);
        close(pipefd[1]);
        exit(EXIT_SUCCESS); 
    }

    close(pipefd[1]);
    char buf[10] = {0};
    read(pipefd[0], buf, 10);
    printf("get data from child : %s\n", buf); 

   return 0;
}
