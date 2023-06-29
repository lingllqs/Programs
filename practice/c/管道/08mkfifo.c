#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>

int main(int argc, char const *argv[])
{
	if (mkfifo("myfifo", 0644) == -1)
	{
		if (errno != EEXIST)
		{
			perror("fail to mkfifo");
			exit(1);
		}
	}

	return 0;
}
