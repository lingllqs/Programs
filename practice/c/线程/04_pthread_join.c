#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>


void *pthread_fun(void *arg)
{
	static int num = 999;
	printf("子线程正在执行\n");
	printf("&num = %p\n", &num);
	return (void *)&num;
}

int main(int argc, char const *argv[])
{
	pthread_t th;
	if (pthread_create(&th, NULL, pthread_fun, NULL) == -1)
	{
		perror("fail to pthread_create");
		exit(1);
	}

	int *num;
	if (pthread_join(th, (void**)&num) != 0)
	{
		perror("fail to pthread_join");
		exit(1);
	}
	printf("ret_val = %d\n", *num);
	printf("ret_val = %p\n", num);

	return 0;
}
