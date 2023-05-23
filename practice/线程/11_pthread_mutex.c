#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <share.h>


int money = 10000;
pthread_mutex_t mymutex;

void *pthread_fun1(void *arg)
{
	int get, yu, shiji;
	get = 10000;
	pthread_mutex_lock(&mymutex);
	printf("张三正在查询余额...\n");
	sleep(1);
	yu = money;
	printf("张三正在取钱...\n");
	sleep(1);
	if (get > yu)
	{
		shiji = 0;
	}
	else
	{
		shiji = get;
		yu = yu - get;
		money = yu;
	}
	printf("张三想取%d,实际取了%d,余额为%d\n", get, shiji, yu);
	pthread_mutex_unlock(&mymutex);
	pthread_exit(NULL);

}
void *pthread_fun2(void *arg)
{
	int get, yu, shiji;
	get = 10000;
	pthread_mutex_lock(&mymutex);
	printf("李四正在查询余额...\n");
	sleep(1);
	yu = money;

	printf("李四正在取钱...\n");
	sleep(1);
	if (get > yu)
	{
		shiji = 0;
	}
	else
	{
		shiji = get;
		yu = yu - get;
		money = yu;
	}
	printf("李四想取%d,实际取了%d,余额为%d\n", get, shiji, yu);
	pthread_mutex_unlock(&mymutex);
	pthread_exit(NULL);

}

int main(int argc, char const *argv[])
{
	ERRP(0 != pthread_mutex_init(&mymutex, NULL), pthread_mutex_init, exit(1));

	pthread_t th1, th2;
	ERRP(pthread_create(&th1, NULL, pthread_fun1, NULL) != 0, pthread_create, exit(1));
	ERRP(pthread_create(&th2, NULL, pthread_fun2, NULL) != 0, pthread_create, exit(1));

	pthread_join(th1, NULL);
	pthread_join(th2, NULL);

	pthread_mutex_destroy(&mymutex);
	return 0;
}

