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

void handler(int, siginfo_t *, void *);

int main(int argc, char *argv[])
{
    struct sigaction act;
    act.sa_sigaction = handler;
    sigemptyset(&act.sa_mask);
    act.sa_flags = SA_SIGINFO;

    if (sigaction(SIGINT, &act, NULL) < 0)
        ERR_EXIT("sigaction");
    for (;;);
    return 0;
}

void handler(int sig, siginfo_t *info, void *cxt )
{
    printf("recv a sig=%d, data=%d\n", sig, info->si_value.sival_int);
}
