#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>


void *fun(void *arg)
{
	while(1)
	{
		printf("hello world\n");
		sleep(1);
	}
}

int main(int argc, char const *argv[])
{
	pthread_t th;
	if (pthread_create(&th, NULL, fun, NULL) == -1)
	{
		perror("fail to pthread_create");
		exit(1);
	}

	sleep(3);
	pthread_cancel(th);
	pthread_join(th, NULL);


	return 0;
}
