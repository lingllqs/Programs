#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <unistd.h>
#include<sys/ipc.h>

int main(void)
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
	printf("text = %s\n", text);
	if (shmdt(text) == -1)
	{
		perror("fail to shmdt");
		exit(1);
	}
	system("ipcs -m");

	return 0;
}
