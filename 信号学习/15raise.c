#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
	int num;

	while(1)
	{
		printf("hello world\n");
		sleep(1);
		num++;
		if (num == 5)
		{
			/*raise(SIGKILL);*/
			/*kill(getpid(), SIGKILL);*/
			abort();
		}
	}

	return 0;
}
