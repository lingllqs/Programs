#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char const *argv[])
{
	int fd[2];
	if (pipe(fd) == -1)
	{
		perror("fail to pipe'n");
		exit(1);
	}
	pid_t pid;
	pid = fork();
		char buf[128] = {};
	if (pid == -1)
	{
		perror("fail to fork");
		exit(1);
	}
	else if (pid > 0)
	{
		close(fd[0]);
		while(1)
		{
			fgets(buf, sizeof(buf), stdin);
			buf[strlen(buf) - 1] = '\0';
			if (write(fd[1], buf, sizeof(buf)) == -1)
			{
				perror("fail to write");
				exit(1);
			}
		}
		close(fd[1]);
	}
	else
	{
		close(fd[1]);
		while(1)
		{
			if (read(fd[0], buf, sizeof(buf)) == -1)
			{
				perror("fail to read");
				exit(1);
			}
			printf("buf = [%s]\n", buf);
		}
		close(fd[0]);
	}

	return 0;
}
