#include<unistd.h>
#include<stdio.h>
#include<errno.h>
#include<signal.h>
#include<stdlib.h>

int main(void)
{
	printf("Entering main ...\n");
	execlp("ps", "ps", "-x", NULL);
	printf("Exiting main ...\n");
	return 0;
}
