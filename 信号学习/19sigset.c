#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

int main(int argc, char const *argv[])
{
	sigset_t set;
	int ret = 0;

	sigemptyset(&set);
	if (sigismember(&set, SIGINT) == 0)
	{
		printf("SIGINT isn't in set\n");
	}
	else
	{
		printf("SIGINT is in set\n");
	}
	sigaddset(&set, SIGINT);
	if (sigismember(&set, SIGINT) == 0)
	{
		printf("SIGINT isn't in set\n");
	}
	else
	{
		printf("SIGINT is in set\n");
	}
	sigdelset(&set, SIGINT);
	if (sigismember(&set, SIGINT) == 0)
	{
		printf("SIGINT isn't in set\n");
	}
	else
	{
		printf("SIGINT is in set\n");
	}
	sigfillset(&set);
	if (sigismember(&set, SIGINT) == 0)
	{
		printf("SIGINT isn't in set\n");
	}
	else
	{
		printf("SIGINT is in set\n");
	}

	return 0;
}
