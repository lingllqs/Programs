#include <stdio.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{
	unsigned int sec;
	sec = alarm(5);
	printf("sec = %d\n", sec);

	sleep(2);

	sec = alarm(8);
	printf("sec = %d\n", sec);
	while(1)
	{
		printf("hello\n");
		sleep(1);
	}
	return 0;
}
