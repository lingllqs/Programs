#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>


void handler(int sig)
{
	printf("SIGINT\n");
}
int main()
{


	if (signal(SIGINT, handler) == SIG_ERR)
	{
		perror("fail to signal");
		exit(1);
	}
	/*sleep(10);*/
	alarm(10);
	while(1)
	{
		printf("hello world\n");
		sleep(1);
	}

	return 0;
}
