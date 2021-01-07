#include <stdio.h>
#include <share.h>
#include <errno.h>

int main(int argc, char const *argv[])
{
	if ((remove("./file.txt")) == -1)
	{
		perror("fail to remove");
		printf("%d\n", errno);
		return -1;
	}
	printf("remove done\n");
	
	return 0;
}
