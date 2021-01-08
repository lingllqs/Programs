#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{
	printf("pid = %d\n", getpid());
	printf("pid = %d\n", getppid());
	printf("pid = %d\n", getpgid(getpid()));
	while(1)
	{}

	return 0;
}
