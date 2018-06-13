#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <errno.h>

#define ERR_EXIT(m) \
	do { \
		perror(m); \
		exit(EXIT_FAILURE); \
	} while(0)

void printsigset(int index, sigset_t *sigset);
void handler(int sig);

int main(int argc, char *argvp[])
{
	sigset_t pset, bset;
	sigemptyset(&bset);
	sigaddset(&bset, SIGINT);

	if (signal(SIGINT, handler) == SIG_ERR)
		ERR_EXIT("signal INT");
	if (signal(SIGQUIT, handler) == SIG_ERR)
		ERR_EXIT("signal QUIT");

	sigprocmask(SIG_BLOCK, &bset, NULL);
	
	int i;
	for (i = 0;i < 1000; ++i){
		printf("In [%d]", getpid());
		fflush(stdout);
		sigpending(&pset);
		printsigset(i, &pset);
		sleep(1);
		if (i == 100000){
			sigset_t uset;
			sigemptyset(&uset);
			sigaddset(&uset, SIGINT);
			sigprocmask(SIG_UNBLOCK, &uset, NULL);
		}
	}

	return 0;
}

void printsigset(int index, sigset_t *sigset)
{
	printf("(%d)", index);fflush(stdout);
	int i;
	for (i = 1; i < NSIG; ++i){
		if (sigismember(sigset, i))
			putchar('1');
		else
			putchar('0');
	}
	printf("\n");
}

void handler(int sig)
{
	printf("In [%d handler]", getpid());
	fflush(stdout);
	sigset_t hset;
	sigprocmask(SIG_BLOCK, NULL, &hset);
	printsigset(9999, &hset);
	if (sig == SIGINT)
		printf("recv a sig = %d\n", sig);
	else if (sig == SIGQUIT){
		sigset_t uset;
		sigemptyset(&uset);
		sigaddset(&uset, SIGINT);
		sigprocmask(SIG_UNBLOCK, &uset, NULL);
	}
}

