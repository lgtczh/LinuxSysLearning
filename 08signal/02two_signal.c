#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
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
    __sighandler_t oldhandler;
    oldhandler = signal(SIGINT, handler);
    
    if (oldhandler == SIG_ERR)
        ERR_EXIT("signal");
    else
        printf("deal signal successfully!\n");
    
    while (getchar() != '\n');

    printf("continue...\n");    
    if (signal(SIGINT, oldhandler) == SIG_ERR)
        ERR_EXIT("signal");
    
    for (;;);
    
    return 0;
}

void handler(int sig)
{
    printf("recv a sig=%d\n", sig);
}
