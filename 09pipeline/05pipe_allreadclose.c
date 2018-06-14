#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <signal.h>

#define ERR_EXIT(m) \
    do { \
        perror(m); \
        exit(EXIT_FAILURE); \
    } while(0)
void handler(int sig)
{
    printf("recv a sig : %d\n", sig);
}

int main(int argc, char *argv[])
{
    signal(SIGPIPE, handler);
    int pipefd[2];
    if (pipe(pipefd) == -1)
        ERR_EXIT("pipe");

    pid_t pid;
    if ((pid = fork()) == -1)
        ERR_EXIT("fork");

    if (pid == 0){
        // 关闭子进程的管道读取端文件描述符
	close(pipefd[0]);
        close(pipefd[1]);
        exit(EXIT_SUCCESS); 
    }

    // 关闭父进程的管道读取端文件描述符
    close(pipefd[0]);
    sleep(1); // 确保子进程关闭了读取端
    int ret = write(pipefd[1], "hello", 5);
    if (ret == -1)
        ERR_EXIT("write");

   return 0;
}
