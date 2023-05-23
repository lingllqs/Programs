#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

void *fun(void *arg)
{
	printf("子线程\n");
	int i;
	/*static char buf[] = "this thread is quited";*/
	static char *buf = "this thread is quited";
	printf("&buf = %p\n", &buf);
	for (i = 0; i < 10; i++)
	{
		if (i == 5)
		{
			pthread_exit(buf);
		}
		printf("hello world\n");
		sleep(1);
	}
}

int main(int argc, char const *argv[])
{
	pthread_t th;
	if (pthread_create(&th, NULL, fun, NULL) == -1)
	{
		perror("fail to pthread_create");
			exit(1);
	}

	char *str;
	pthread_join(th, (void **)&str);
	printf("str = %s\n", str);
	return 0;
}
