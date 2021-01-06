#include <stdio.h>

int main(int argc, char *argv[])
{
	int i;
	i = 100;
	printf("%d\n", i);
	for (i = 0; i < 10; i++)
	{
		printf("%d ", i+1);
	}
	return 0;
}
