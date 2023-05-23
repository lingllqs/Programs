#include <stdio.h>
#include <unistd.h>
#include <semaphore.h>
#include <pthread.h>


char ch = '0';

sem_t sem_g, sem_p;

void *pthread_g(void *arg)
{
	while(1)
	{
		sem_wait(&sem_g);
		ch++;
		sleep(1);
		sem_post(&sem_p);
	}
}

void *pthread_p(void *arg)
{
	while(1)
	{
		sem_wait(&sem_p);
		printf("%c", ch);
		fflush(stdout);
		sem_post(&sem_g);
	}
}

int main(int argc, char const *argv[])
{
	sem_init(&sem_g, 0, 0);
	sem_init(&sem_p, 0, 1);


	pthread_t th1, th2;

	pthread_create(&th1, NULL, pthread_g, NULL);
	pthread_create(&th2, NULL, pthread_p, NULL);

	pthread_join(th1, NULL);
	pthread_join(th2, NULL);

	return 0;
}
