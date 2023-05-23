#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{
	int fd;
	fd = open("file.txt", O_RDWR| O_CREAT, 0664);
	if (-1 == fd)
	{
		perror("fail to open");
		return -1;
	}

    /*
	 *ssize_t bytes;
	 *bytes = write(fd, "hello world", 12);
	 *if (-1 == bytes)
	 *{
	 *    perror("fail to write");
	 *    return -1;
	 *}
     */
	char buf[128] = "";
	read(fd, buf, sizeof(buf));
	printf("buf = %s\n", buf);
	close(fd);

	
	return 0;
}
