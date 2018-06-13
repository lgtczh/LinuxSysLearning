#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <errno.h>

#define ERR_EXIT(m) \
    do{ \
        perror(m); \
        exit(EXIT_FAILURE); \
    } while(0)

void handler(int);

int main(int argc, char *argv[])
{
    struct sigaction act;
    act.sa_handler = handler;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;

    sigset_t sigset;
    sigemptyset(&sigset);
    sigaddset(&sigset, SIGINT);
    sigaddset(&sigset, SIGRTMIN);
    sigprocmask(SIG_BLOCK, &sigset, NULL);

    if (sigaction(SIGINT, &act, NULL) < 0)
        ERR_EXIT("sigaction");
    if (sigaction(SIGRTMIN, &act, NULL) < 0)
	ERR_EXIT("sigaction");
    if (sigaction(SIGUSR1, &act, NULL) < 0)
        ERR_EXIT("sigaction");
    
    for (;;)
        pause();

    return 0;
}

void handler(int sig)
{
    if (sig == SIGINT || sig == SIGRTMIN)
        printf("recv a sig=%d\n", sig);
    else{
        sigset_t s;
        sigemptyset(&s);
        sigaddset(&s, SIGINT);
        sigaddset(&s, SIGRTMIN);
        sigprocmask(SIG_UNBLOCK, &s, NULL);
    }
}
