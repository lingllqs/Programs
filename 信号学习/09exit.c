#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>

void fun()
{
	printf("fun");
	//return ;
	//exit(0);
	_exit(0);
}
int main()
{
	printf("hello world\n");

	fun();

	printf("nihao");

	return 0;
}
