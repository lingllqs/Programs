#include <stdio.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{
	int fd;
	fd = dup(1);
	write(fd, "hello world\n", 12);

	return 0;
}
