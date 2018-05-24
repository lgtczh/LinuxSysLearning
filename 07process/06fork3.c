#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#define ERR_EXIT(m) \
	do { \
		perror(m); \
		exit(EXIT_FAILURE); \
	} while(0)

int main(void)
{
	fork();
	fork();
	fork();
	printf("ok:PID=%d, PPID=%d\n",getpid(), getppid());
	return 0;
}
