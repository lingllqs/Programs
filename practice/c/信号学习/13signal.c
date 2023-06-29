#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>

int main(int argc, char const *argv[])
{
	pid_t pid;
	pid = fork();

	if (-1 == pid)
	{
		perror("fail to fork");	
		exit(1);
	}
	else if (0 == pid)
	{
		printf("son\n");
		printf("3sec later kill father process\n");
		sleep(3);
		kill(getppid(), SIGKILL);
	}
	else
	{
		while(1)
		{
			printf("father\n");
			sleep(1);
		}
	}

	return 0;
}
