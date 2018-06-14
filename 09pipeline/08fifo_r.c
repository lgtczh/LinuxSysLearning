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
    int ret = mkfifo("test", 0644);
    if (ret == -1)
        ERR_EXIT("mkfifo");

    int fd = open("test", O_RDONLY);
    printf("open successfully\n");
    return 0;
}
