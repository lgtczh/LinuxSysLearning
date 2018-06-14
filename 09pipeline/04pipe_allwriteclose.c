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

    pid_t pid;
    if ((pid = fork()) == -1)
        ERR_EXIT("fork");

    if (pid == 0){
	close(pipefd[0]);
        // 关闭子进程的管道写入端文件描述符
        close(pipefd[1]);
        exit(EXIT_SUCCESS); 
    }

    close(pipefd[1]);
    sleep(1); 
    char buf[10] = {0};
    int ret = read(pipefd[0], buf, 10);
    if (ret == -1)
        ERR_EXIT("read");
    else
        printf("read return : %d\n", ret);

   return 0;
}
