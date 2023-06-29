#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>


void *pthread_fun1(void *arg)
{
	printf("子线程1正在执行\n");
	sleep(1);
	printf("*******************\n");
}
void *pthread_fun2(void *arg)
{
	printf("子线程2正在执行\n");
	sleep(1);
	printf("------------------\n");
}

int main(int argc, char const *argv[])
{
	printf("主控线程正在执行\n");

	pthread_t thread1;
	pthread_t thread2;
	if (pthread_create(&thread1, NULL, pthread_fun1, NULL) == -1)
	{
		perror("fail to pthread_create");
		exit(1);
	}
	if (pthread_create(&thread2, NULL, pthread_fun2, NULL) == -1)
	{
		perror("fail to pthread_create");
		exit(1);
	}
    /*
	 *sleep(1);
     */
	while(1);
	return 0;
}
