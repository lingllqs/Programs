#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

typedef void (*sighandler_t)(int);
sighandler_t ret;
void handler(int sig)
{
	printf("sig\n");
	if (signal(SIGINT, ret) == SIG_ERR)
	{
		perror("fail to signal");
		exit(1);
	}
}
int main(int argc, char const *argv[])
{
	if ((ret = (signal(SIGINT, handler))) == SIG_ERR)
	{
		perror("fail to signal");
		exit(1);
	}
	while(1)
	{
		printf("hello world\n");
		sleep(1);
	}

	return 0;
}
