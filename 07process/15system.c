#include <unistd.h>
#include <stdlib.h>

#define ERR_EXIT(m) \
    do{ \
        perror(m); \
        exit(EXIT_FAILURE); \
    }while (0)

int main(int argc, char *argv[])
{
    system("ls -l | wc -w");
     return 0;
}

