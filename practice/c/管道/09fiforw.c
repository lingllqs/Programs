#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>


int main(int argc, char const *argv[])
{
	if (mkfifo("myfifo", 0664) == -1)
	{
		if (errno != EEXIST)
		{
			perror("fail to mkfifo");
			exit(1);
		}
	}

	int fd = open("myfifo", O_RDWR);
	if (fd == -1)
	{
		perror("fail to open");
		exit(1);
	}
	if (write(fd, "hello world", 12) == -1)
	{
		perror("fail to write");
		exit(1);
	}
	char buf[128] = {};
	if (read(fd, buf, sizeof(buf)) == -1)
	{
		perror("fail to read");
		exit(1);
	}
	printf("buf = [%s]\n", buf);

	return 0;
}
