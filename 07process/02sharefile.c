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

int main(int argc, char *argv[])
{
	signal(SIGCHLD, SIG_IGN);
	printf("before fork pid = %d\n", getpid());

	int fd;
	fd = open("test.txt", O_WRONLY);
	if (fd == -1)
		ERR_EXIT("open error");

	pid_t pid;
	pid = fork();
	if (pid == -1)
		ERR_EXIT("fork error");
	
	if (pid > 0)
	{
		printf("this is parent[pid=%d, child pid=%d]\n", getpid(), pid);
		printf("in parent fd = %d\n", fd);
		write(fd, "parent", 6);
		sleep(10);
	}else if (pid == 0)
	{
		printf("this is child[pid=%d, parent pid=%d]\n", getpid(), getppid());
		printf("in child fd = %d\n", fd);
		write(fd, "child", 5);
	}
	
	return 0;
}
