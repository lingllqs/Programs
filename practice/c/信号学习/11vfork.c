#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int a = 3;
int main(int argc, char const *argv[])
{
	int b = 4;

	pid_t pid;
	pid = vfork();
	if (pid == -1)
	{
		perror("fail to vfork");
		exit(0);
	}
	else if (pid == 0)
	{
		int i;
		a++;b++;
		for (i = 0; i < 5; i++)
		{
			printf("son: a = %d, b = %d\n", a, b);
			sleep(1);
		}
		exit(3);
	}
	else
	{
		int i = 5;
		while(i--)
		{
			printf("father: a = %d, b = %d\n", a, b);
			sleep(1);
		}
		int status = 0;
		waitpid(-1, &status, 0);
		if (WIFEXITED(status) != 0)
		{
			printf("%d\n", WEXITSTATUS(status));
		}
	}

	return 0;
}
