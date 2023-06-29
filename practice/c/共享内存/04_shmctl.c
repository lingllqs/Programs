#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

int main(int argc, char const *argv[])
{
	key_t mykey;
	if ((mykey = ftok(".", 127)) == -1)
	{
		perror("fail to ftok");
		exit(1);
	}
	printf("mykey = %#x\n", mykey);

	int shmid;
	if ((shmid = shmget(mykey, 1024, IPC_CREAT|0664)) == -1)
	{
		perror("fail to shmget");
		exit(1);
	}
	printf("shmid = %d\n", shmid);

	system("ipcs -m");

	if (shmctl(shmid, IPC_RMID, NULL) == -1)
	{
		perror("fqil to shmctl");
		exit(1);
	}
	system("ipcs -m");

	

	return 0;
}
