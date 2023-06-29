#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>

sem_t sem;

void printer(char *str)
{
	sem_wait(&sem);
	while(*str)
	{
		putchar(*str);
		fflush(stdout);
		sleep(1);
		*str++;
	}
	sem_post(&sem);
}

void *pthread_fun1(void *arg)
{
	char *str = "hello";
	printer(str);
}

void *pthread_fun2(void *arg)
{
	char *str = "world";
	printer(str);
}

int main(int argc, char const *argv[])
{
	sem_init(&sem, 0, 1);

	pthread_t th1, th2;
	pthread_create(&th1, NULL, pthread_fun1, NULL);
	pthread_create(&th2, NULL, pthread_fun2, NULL);

	pthread_join(th1, NULL);
	pthread_join(th2, NULL);

	putchar(10);
	sem_destroy(&sem);

	return 0;
}
