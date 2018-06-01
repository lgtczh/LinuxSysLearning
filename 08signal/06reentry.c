#include <unistd.h>
#include <stdio.h>
#include <signal.h>

typedef struct
{
    int a;
    int b;
} DATA;

DATA g_data;

void handler(int sig);

int main(int argc, char *argvp[])
{
    DATA zeros = {0, 0};
    DATA ones = {1, 1};
    signal(SIGALRM, handler);
    
    g_data = zeros;
    alarm(1);
 
    for (;;){
        g_data.a = zeros.a;
        g_data.b = zeros.b;
        g_data.a = ones.a;
        g_data.b = ones.b;
    }
    return 0;
}
void unsafe_fun()
{
    printf("g_data = (%d, %d)\n", g_data.a, g_data.b);
}
void handler(int sig)
{
    unsafe_fun();
    alarm(1);
}
