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

void printsigset(sigset_t *sigset);
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

	for (;;){
		sigpending(&pset);
		printsigset(&pset);
		sleep(2);
	}

	return 0;
}

void printsigset(sigset_t *sigset)
{
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
	if (sig == SIGINT)
		printf("recv a sig = %d\n", sig);
	else if (sig == SIGQUIT){
		sigset_t uset;
		sigemptyset(&uset);
		sigaddset(&uset, SIGINT);
		sigprocmask(SIG_UNBLOCK, &uset, NULL);
	}
}

