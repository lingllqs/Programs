#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>


void *pthread_fun(void *arg)
{
	printf("子线程正在执行\n");
}

int main(int argc, char const *argv[])
{
	printf("主控线程正在执行\n");

	pthread_t thread;
	if (pthread_create(&thread, NULL, pthread_fun, NULL) == -1)
	{
		perror("fail to pthread_create");
		exit(1);
	}
	sleep(1);
	return 0;
}
