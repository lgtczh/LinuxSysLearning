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
        dup2(pipefd[1], STDOUT_FILENO);
        close(pipefd[0]);
        close(pipefd[1]);
        execlp("ls", "ls", NULL);
        fprintf(stderr, "error execute ls\n");
	exit(EXIT_FAILURE);
    }

    dup2(pipefd[0], STDIN_FILENO);
    close(pipefd[0]);
    close(pipefd[1]);
    execlp("wc", "wc", "-w", NULL);
    fprintf(stderr, "error execute wc\n");
    exit(EXIT_FAILURE);

   return 0;
}
