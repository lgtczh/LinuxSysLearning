#include<unistd.h>
#include<stdio.h>
#include<errno.h>
#include<signal.h>
#include<stdlib.h>

int main(void)
{
	printf("Entering main...\n");
	int ret = execl("/bin/ls", "ls","-l", NULL);
	if (ret == -1)
		perror("execl");
	printf("Exiting main ...\n");
	return 0;
}
