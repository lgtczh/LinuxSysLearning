#include <unistd.h>
#include <stdio.h>
#include <signal.h>

void handler(int sig);

int main(int argc, char *argvp[])
{
    signal(SIGALRM, handler);
    alarm(1);
    for (;;){
        pause();
    }
    return 0;
}

void handler(int sig)
{
    printf("recv a sig=%d\n", sig);
}
