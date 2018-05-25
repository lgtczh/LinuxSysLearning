#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>

int main(void)
{
	printf("Entering main...\n");
	int flag = fcntl(1, F_GETFD);
	fcntl(1, F_SETFD, flag | FD_CLOEXEC);
	
	execlp("./09hello","09hello", NULL);
	printf("Exiting main ...\n");
	return 0;
}
