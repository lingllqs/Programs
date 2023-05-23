#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{
	int fd_file;
	fd_file = open("file.txt", O_WRONLY | O_CREAT | O_TRUNC, 0664);
	if (fd_file == -1)
	{
		perror("fail to open");
		exit(1);
	}
	dup2(fd_file, 1);
	printf("nihao\n");
	printf("fd_file = %d\n", fd_file);

	return 0;
}
