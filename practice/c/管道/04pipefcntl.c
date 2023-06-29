#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

int main(int argc, char const *argv[])
{
	int fd[2];
	char buf[132] = {"hello world"};
	if (pipe(fd) == -1)
	{
		perror("fail to pipe");
		exit(1);
	}

	pid_t pid;
	pid = fork();
	if (pid == -1)
	{
		perror("fail to fork");
		exit(1);
	}
	else if (pid == 0)//子进程写
	{
		while(1)
		{
			sleep(5);
			if (write(fd[1], buf, strlen(buf)) == -1)
			{
				perror("fail to write");
				exit(1);
			}
		}
	}
	else//父进程读
	{
		fcntl(fd[0], F_SETFL, O_NONBLOCK);
		while(1)
		{
			memset(buf, 0, sizeof(buf));
			sleep(1);
			read(fd[0], buf, sizeof(buf));
            /*
			 *if (read(fd[0], buf, sizeof(buf)) == -1)
			 *{
			 *    perror("fail to read");
			 *    exit(1);
			 *}
             */
			printf("buf = [%s]\n", buf);
		}
	}

	return 0;
}
