#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<sys/types.h>
#include<sys/wait.h>

#define ERR_EXIT(m) \
    do{ \
        perror(m); \
        exit(EXIT_FAILURE); \
    }while(0)

int main(void)
{
    pid_t pid = fork();
    if (pid == -1)
        ERR_EXIT("fork");

    if (pid == 0){
        printf("I am child process,my pid is %d, I am working...\n", getpid());
        sleep(2);
        printf("I will exit!\n");
        //exit(1);
        abort();
    }

    printf("This is parent...\n");
    int status;
    pid_t cpid = wait(&status);
    printf("Child process pid = %d\n", cpid);
    if (WIFEXITED(status))
        printf("Child exited normally, exit status = %d\n", WEXITSTATUS(status));
    else if (WIFSIGNALED(status))
        printf("Child was termed by signal: %d\n", WTERMSIG(status));
    else if(WIFSTOPPED(status))
        printf("child stopped, signal number = %d\n", WSTOPSIG(status));

    return 0;
}
