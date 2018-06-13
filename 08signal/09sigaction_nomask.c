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

void handler(int sig);

int main(int argc, char *argvp[])
{
    struct sigaction act;
    act.sa_handler = handler;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;

    if (sigaction(SIGINT, &act, NULL) < 0)
        ERR_EXIT("sigaction");
    for (;;);
    return 0;
}

void handler(int sig)
{
    printf("recv a sig=%d\n", sig);
    sleep(5);
    printf("handler over\n");
}
