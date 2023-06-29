#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>

int main(int argc, char const *argv[])
{
	key_t mykey;
	if ((mykey = ftok(".", 100)) == -1)
	{
		perror("fail to ftok");
		exit(1);
	}

	printf("mykey = %#x\n", mykey);
	printf("mykey = %x\n", mykey);

	return 0;
}
