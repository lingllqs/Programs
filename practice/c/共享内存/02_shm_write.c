#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>

int main(int argc, char const *argv[])
{
	key_t mykey;
	if ((mykey = ftok(".", 100)) == -1)
	{
		perror("fail to ftok");
		exit(1);
	}
	printf("mykey = %#x\n", mykey);

	int shmid;
	if ((shmid = shmget(mykey, 500, IPC_CREAT|0666)) == -1)
	{
		perror("fail to shmget");
		exit(1);
	}
	printf("shmid = %d\n", shmid);

	char *text;
	if ((text = shmat(shmid, NULL, 0)) == (void *)-1)
	{
		perror("fail to shmat");
		exit(1);
	}

	strcpy(text, "hello world");
	if (shmdt(text) == -1)
	{
		perror("fail to shmdt");
		exit(1);
	}
	system("ipcs -m");

	return 0;
}
