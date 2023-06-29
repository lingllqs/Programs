#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

void *pthread_fun(void *arg)
{
	printf("子线程正在执行\n");
	sleep(3);
	printf("子线程正在推出\n");
}

int main(int argc, char const *argv[])
{
	pthread_t th;
	if (pthread_create(&th, NULL, pthread_fun, NULL) == -1)
	{
		perror("fail to pthread_create");
		exit(1);
	}
	if (pthread_detach(th) != 0)
	{
		perror("fail to pthread_detach");
		exit(1);
	}
	while(1)
	{
		printf("hello world\n");
		sleep(1);
	}

	return 0;
}
