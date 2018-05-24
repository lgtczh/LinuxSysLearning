#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define ERR_EXIT(m) \
	do { \
		perror(m); \
		exit(EXIT_FAILURE); \
	} while(0)

int gval = 100;

int main(int argc, char *argv[])
{
	signal(SIGCHLD, SIG_IGN);

	pid_t pid;
	pid = vfork();
	if (pid == -1)
		ERR_EXIT("fork error");
	
	if (pid > 0)
	{
		sleep(1);
		printf("this is parent[pid=%d, child pid=%d],gval=%d\n", getpid(), pid, gval);
	}else if (pid == 0)
	{
		gval ++;
		printf("this is child[pid=%d, parent pid=%d],gval=%d\n", getpid(), getppid(), gval);
		_exit(EXIT_SUCCESS);
	}
	
	return 0;
}
