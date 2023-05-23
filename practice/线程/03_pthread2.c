#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>


int num = 100;
void *pthread_fun1(void *arg)
{
	printf("子线程1正在执行\n");
	printf("1: num = %d\n", num);
	num++;
	printf("arg = %d\n", *(int *)arg);
}
void *pthread_fun2(void *arg)
{
	printf("子线程2正在执行\n");
	sleep(1);
	printf("2: num = %d\n", num);
	printf("arg = %d\n", *(int *)arg);
}

int main(int argc, char const *argv[])
{
	printf("主控线程正在执行\n");

	pthread_t thread1;
	pthread_t thread2;
	int n = 33;
	if (pthread_create(&thread1, NULL, pthread_fun1, (void*)&n) == -1)
	{
		perror("fail to pthread_create");
		exit(1);
	}
	if (pthread_create(&thread2, NULL, pthread_fun2, (void*)&n) == -1)
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
