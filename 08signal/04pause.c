#include <unistd.h>
#include <stdio.h>
#include <signal.h>

void handler(int sig);

int main(int argc, char *argvp[])
{
    signal(SIGINT, handler);
    for (;;){
        pause();
        printf("pause return\n");
    }
    return 0;
}

void handler(int sig)
{
    printf("recv a sig=%d\n", sig);
    sleep(1);
}
