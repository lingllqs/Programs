#include <signal.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
	int ret;
	sigset_t set;
	sigemptyset(&set);
	sigaddset(&set, SIGINT);
	ret = sigismember(&set, SIGINT);
	if (ret == 1)
	{
		printf("SIGINT is in the set\n");
	}
	sigprocmask(SIG_BLOCK, &set, NULL);
	for (ret = 0; ret < 10; ret++)
	{
		printf("SIGINT is in sigprocmask\n");
		sleep(1);
	}
	sigprocmask(SIG_UNBLOCK, &set, NULL);
	for (ret = 0; ret < 10; ret++)
	{
		printf("SIGINT is not in sigprocmask\n");
		sleep(1);
	}


	return 0;
}
