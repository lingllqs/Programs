#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


int a = 666;
int main(int argc, char const *argv[])
{
	int b = 777;
	static int c = 888;
	pid_t pid;
	pid = fork();
	if (pid < 0)
	{
		perror("fail to fork");
		return -1;
	}
	else if (pid > 0)
	{
		a++;b++;c++;
		printf("parent: a = %d, b = %d, c = %d\n", a, b, c);
	}
	
	else
	{
		sleep(1);
		printf("child: a = %d, b = %d, c = %d\n", a, b, c);
	}

	return 0;
}
