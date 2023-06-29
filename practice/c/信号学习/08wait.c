#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main()
{
	pid_t pid;
	pid = fork();

	if (pid == -1)
	{
		perror("fail to fork");
		return -1;
	}
	else if (pid == 0)
	{
		int i = 0;
		for (i = 0; i < 5; i++)
		{
			printf("son\n");
			sleep(1);
		}
		exit(7);
	}
	else
	{
		int status = 0;
		/*wait(&status);*/
		waitpid(pid, &status, 0);//WNOHANG WUNTRACED
		unsigned int ret;
		ret = WIFEXITED(status);
		if (ret != 0)
		{
			printf("%d\n", WEXITSTATUS(status));
		}
		printf("father\n");
	}

	return 0;
}
