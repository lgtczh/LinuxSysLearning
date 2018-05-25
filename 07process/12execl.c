#include<unistd.h>
#include<stdio.h>
#include<errno.h>
#include<signal.h>
#include<stdlib.h>

int main(void)
{
	printf("Entering main...\n");
	execl("12print_env", "12print_env", NULL);
	printf("Exiting main ...\n");
	return 0;
}
