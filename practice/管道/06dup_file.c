#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
	int fd_file;
	fd_file = open("file.txt", O_WRONLY | O_CREAT | O_TRUNC, 0664);
	if (fd_file == -1)
	{
		perror("fail to open");
		exit(1);
	}
	printf("fd_file = %d\n", fd_file);
	close(1);
	int fd = dup(fd_file);
	printf("hello world\n");
	printf("fd = %d\n", fd);
	printf("fd_file = %d\n", fd_file);

	return 0;
}
