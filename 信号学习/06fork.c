#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{
	pid_t pid;
	pid = fork();
	if (pid > 0)//父进程
	{
		printf("parent:pid=%d getpid=%d\n", pid, getpid());
	}
	else if (pid == 0)//子进程
	{
		printf("child:pid=%d getpid=%d\n", pid, getpid());
	}
	else
	{
		printf("err:pid=%d getpid=%d\n",pid, getpid());
	}

	printf("main:pid=%d getpid=%d\n",pid, getpid());
	while(1)
	{}

	return 0;
}
