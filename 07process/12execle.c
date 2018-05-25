#include<unistd.h>
#include<stdio.h>
#include<errno.h>
#include<signal.h>
#include<stdlib.h>

int main(void)
{
        char *const envp[] = {"AA=11", "BB=22", NULL};
	printf("Entering main...\n");
	execle("12print_env", "12print_env", NULL, envp);
	printf("Exiting main ...\n");
	return 0;
}
