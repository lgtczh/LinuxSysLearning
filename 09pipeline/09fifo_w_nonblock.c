#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define ERR_EXIT(m) \
    do { \
        perror(m); \
        exit(EXIT_FAILURE); \
    } while(0)

int main(int argc, char *argv[])
{
    int fd = open("test", O_WRONLY | O_NONBLOCK);
    if (fd == -1)
       ERR_EXIT("open");
    printf("open successfully\n");
    return 0;
}
