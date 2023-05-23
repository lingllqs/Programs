#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

int main(int argc, char const *argv[])
{
	key_t key;
	if ((key = ftok(".", 100)) == -1)
	{
		perror("fail to ftok");
		exit(1);
	}

	int msgid;
	if ((msgid = msgget(key, IPC_CREAT|0666)) == -1)
	{
		perror("fail to msgid");
		exit(1);
	}

	system("ipcs -q");
	if (msgctl(msgid, IPC_RMID, NULL) == -1)
	{
		printf("fail to msgctl");
		exit(1);
	}
	system("ipcs -q");

	return 0;
}
