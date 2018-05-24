#include <unistd.h>
#include <stdio.h>

int main(void)
{
	printf("hello world");
	fflush(stdout);
	_exit(0);
}
