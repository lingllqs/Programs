#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <share.h>

int main(int argc, char const *argv[])
{
	int fd[2];
	ERRP(pipe(fd) == -1, pipe, exit(1));
	printf("fd[0] = %d\nfd[1] = %d\n", fd[0], fd[1]);

	ssize_t bytes;
	ERRP((bytes = write(fd[1], "hello wrold", 12)) == -1, write, exit(1));

	char buf[128] = {};
	ERRP((bytes = read(fd[0], buf, sizeof(buf))) == -1, read, exit(1));

	printf("buf = [%s]\nbytes = %ld\n", buf, bytes);

	//管道中没有数据会阻塞
	ERRP((bytes = read(fd[0], buf, sizeof(buf))) == -1, read, exit(1));
	printf("buf = [%s]\nbytes = %ld\n", buf, bytes);
	return 0;
}
