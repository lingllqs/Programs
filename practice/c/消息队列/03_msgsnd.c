#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <share.h>


typedef struct{
	long mtype;
	char mtext[128];
}MSG;

int main(int argc, char const *argv[])
{
	key_t mykey;
	ERRP((mykey = ftok(".", 100)) == -1, ftok, exit(1));
	printf("mykey = %#x\n", mykey);

	int msgid;
	ERRP((msgid = msgget(mykey, IPC_CREAT | 0664)) == -1, msgget, exit(1));
	printf("msgid = %d\n", msgid);

	MSG msg1 = {1, "hello world"};
	MSG msg2 = {2, "nihao"};
	ERRP(-1 == (msgsnd(msgid, &msg1, sizeof(MSG)-sizeof(long), 0)), msgsnd, exit(1));
	ERRP(-1 == (msgsnd(msgid, &msg2, sizeof(MSG)-sizeof(long), 0)), msgsnd, exit(1));

	system("ipcs -q");

	return 0;
}
