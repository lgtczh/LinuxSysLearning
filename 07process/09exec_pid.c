#include<unistd.h>
#include<stdio.h>
#include<errno.h>
#include<signal.h>
#include<stdlib.h>

int main(void)
{
	printf("Entering main, pid = %d\n", getpid());
	int ret = execlp("09hello", "09hello", NULL);
	if (ret == -1)
		perror("execlp");
	printf("Exiting main ...\n");
	return 0;
}
