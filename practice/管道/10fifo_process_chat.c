#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char const *argv[])
{
	int fd_w;
	int fd_r;
	if (mkfifo("./myfifo1", 0664) == -1)
	{
		if (errno != EEXIST)
		{
		perror("fail to mkfifo");
		exit(1);
		}
	}
	if (mkfifo("./myfifo2", 0664) == -1)
	{
		if (errno != EEXIST)
		{
		perror("fail to mkfifo");
		exit(1);
		}
	}
	if ((fd_w = open("myfifo1", O_RDWR)) == -1)
	{
		if (errno != EEXIST)
		{
			perror("fail to open");
			exit(1);
		}
	}
	if ((fd_r = open("myfifo2", O_RDWR)) == -1)
	{
		if (errno != EEXIST)
		{
			perror("fail to open");
			exit(1);
		}
	}

	char buf[1024] = {};
	pid_t pid;
	pid = fork();
	if (pid < 0)
	{
		perror("fail to fork");
		exit(1);
	}
	else if (pid == 0)
	{
		while(1)
		{
			memset(buf, 0, sizeof(buf));
			fgets(buf, sizeof(buf), stdin);
			buf[strlen(buf) - 1] = '\0';
			if (write(fd_w, buf, sizeof(buf)) == -1)
			{
				perror("fail to write");
				exit(1);
			}
		}
	}
	else
	{
		while(1)	
		{
			memset(buf, 0, sizeof(buf));
			if (read(fd_r, buf, sizeof(buf)) == -1)
			{
				perror("fail to read");
				exit(1);
			}
			printf("buf = [%s]\n", buf);
		}
	}

	return 0;
}
