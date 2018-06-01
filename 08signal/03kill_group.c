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
        kill(-getpgrp(), SIGUSR1);
        exit(EXIT_SUCCESS);
    }
    int n = 5;
    do {
        n = sleep(n);
    } while (n > 0);

    
    return 0;
}

void handler(int sig)
{
    printf("recv a sig=%d\n", sig);
}
