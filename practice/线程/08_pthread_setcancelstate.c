#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>
#include <pthread.h>


void *fun(void *arg)
{
	pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, NULL);
	while(1)
	{
		printf("子线程正在执行\n");
		sleep(1);
	}
}

int main(void)
{
	pthread_t th;
	if (pthread_create(&th, NULL, fun, NULL) == -1)
	{
		perror("fail to pthread_create");
		exit(1);
	}
	pthread_cancel(th);
	pthread_join(th, NULL);

	return 0;
}
