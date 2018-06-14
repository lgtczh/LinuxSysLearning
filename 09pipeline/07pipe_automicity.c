#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


#define ERR_EXIT(m) \
    do { \
        perror(m); \
        exit(EXIT_FAILURE); \
    } while(0)

#define INPUT_SIZE 68*1024 //68K

int main(int argc, char *argv[])
{
    char a[INPUT_SIZE], b[INPUT_SIZE];
    memset(a, 'A', sizeof(a));
    memset(b, 'B', sizeof(b));

    int pipefd[2];
    if (pipe(pipefd) == -1)
        ERR_EXIT("pipe");

    pid_t pid;
    if ((pid = fork()) == -1)
        ERR_EXIT("first fork");
    if (pid == 0){
        close(pipefd[0]);
        int ret = write(pipefd[1], a, sizeof(a));
	printf("aPid = %d, write %d bytes to pipe\n", getpid(), ret);
        exit(EXIT_SUCCESS); 
    }

    
    if((pid = fork()) == -1)
        ERR_EXIT("second fork");
    if (pid == 0){
        close(pipefd[0]);
        int ret = write(pipefd[1], b, sizeof(b));
        printf("bPid = %d, write %d bytes to pipe\n", getpid(), ret);
        exit(EXIT_SUCCESS);
    }

    close(pipefd[1]);
    sleep(1);
    int fd = open("childWritePipe", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    char buf[1024*4] = {0};
    int n = 1;
    while(1){
        int ret = read(pipefd[0], buf, sizeof(buf));
        if (ret == -1)
            ERR_EXIT("read");
        else if (ret == 0)
            break;
        printf("n = %02d, pid = %d, read %d bytes from pipe , buf[4095] = %c\n", n++, getpid(), ret, buf[4095]);
        write(fd, buf, ret);
    }
   return 0;
}
