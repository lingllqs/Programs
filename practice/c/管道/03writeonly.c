#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void handler(int sig)
{
	printf("SIGPIPE\n");
}
int main(int argc, char const *argv[])
{
	signal(SIGPIPE, handler);
	int fd[2];
	if (pipe(fd) == -1)
	{
		perror("fail to pipe");
		exit(1);
	}
	close(fd[0]);
	int num = 0;
	while(1)
	{
		if (write(fd[1], "6666", 1024) == -1)
		{
			perror("fail to write");
			exit(1);
		}
		num++;
	}
	printf("num = %d\n", num);


	return 0;
}
