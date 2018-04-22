#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
    int ret;
    ret = close(10);
/*    
    if (ret == -1)
        perror("close error");

*/
    if (ret == -1)
        fprintf(stderr, "close error with msg: %s\n", strerror(errno));

    return 0;
}

