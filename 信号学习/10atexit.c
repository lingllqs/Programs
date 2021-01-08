#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>


void fun1(void)
{
	printf("fun1\n");
}
void fun2(void)
{
	printf("fun2\n");
}
void fun3(void)
{
	printf("fun3\n");
}
int main(int argc, char const *argv[])
{
	atexit(fun1);
	atexit(fun2);
	atexit(fun3);
	printf("3sec later\n");
	sleep(3);

	return 0;
}
