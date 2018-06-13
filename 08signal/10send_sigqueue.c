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

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "Usage %s pid\n", argv[0]);
	exit(EXIT_FAILURE);
    }
    pid_t pid = atoi(argv[1]);
    union sigval v;
    v.sival_int = 100;
    sigqueue(pid, SIGINT, v);
    return 0;
}

