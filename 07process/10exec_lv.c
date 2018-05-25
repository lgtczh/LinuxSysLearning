#include<unistd.h>
#include<stdio.h>
#include<errno.h>
#include<signal.h>
#include<stdlib.h>

int main(void)
{
	char *const args[] = {"ls", "-l", NULL};
	printf("Entering main...\n");
	//execlp("ls", "ls","-l", NULL);
	execvp("ls", args);
	printf("Exiting main ...\n");
	return 0;
}
