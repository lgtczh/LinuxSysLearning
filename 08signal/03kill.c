#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <errno.h>

#define ERR_EXIT(m) \
    do { \
        perror(m); \
        exit(EXIT_FAILURE); \
    } while(0)

void handler(int sig);

int main(int argc, char *argvp[])
{
    if (signal(SIGUSR1, handler) == SIG_ERR)
        ERR_EXIT("signal");
    
    pid_t pid = fork();
    if (pid == -1)
        ERR_EXIT("fork");
    if (pid == 0){
        kill(getppid(), SIGUSR1);
        exit(EXIT_SUCCESS);
    }
    
    sleep(5);
    
    return 0;
}

void handler(int sig)
{
    printf("recv a sig=%d\n", sig);
}
