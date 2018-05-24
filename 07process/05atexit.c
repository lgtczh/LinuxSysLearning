#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#define ERR_EXIT(m) \
	do { \
		perror(m); \
		exit(EXIT_FAILURE); \
	} while(0)

void my_exit1()
{
	printf("my exit1 ...\n");

}
void my_exit2()
{
	printf("my exit2 ...\n");
}

int main(void)
{
	atexit(my_exit1);
	atexit(my_exit2);
	return 0;
}
