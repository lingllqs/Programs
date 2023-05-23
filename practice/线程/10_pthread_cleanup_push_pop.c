#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>


void myclean(void *arg)
{
	printf("线程清理函数\n");
	printf("str = %s\n", (char*)arg);
	free((char*)arg);
}
void *pthread_fun(void *arg)
{
	char *str = NULL;
	str = (char*)malloc(100);
	bzero(str,100);
	strcpy(str, "this is a str");
	pthread_cleanup_push(myclean, str);
    /*
	 *while(1)
	 *{
	 *    sleep(1);
	 *    printf("子线程正在执行\n");
	 *}
     */
	int i;
	for (i = 0; i < 10; i++)
	{
		printf("子线程正在执行");
		fflush(NULL);
		sleep(1);
		if (i == 5)
		{
			pthread_exit(NULL);
		}
	}
	pthread_cleanup_pop(1);
}

int main(int argc, char const *argv[])
{
	pthread_t th;
	pthread_create(&th, NULL, pthread_fun, NULL);
    /*
	 *sleep(3);
	 *pthread_cancel(th);
     */
	pthread_join(th, NULL);
	printf("进程结束\n");

	return 0;
}
