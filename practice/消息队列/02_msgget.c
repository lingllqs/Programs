#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <share.h>
#include <sys/msg.h>

int main(int argc, char const *argv[])
{
	key_t mykey;
	ERRP((mykey = ftok(".", 100)) == -1, ftok, exit(1));
	printf("mykey = %#x\n", mykey);

	int msgid;
	ERRP((msgid = msgget(mykey, IPC_CREAT | 0666)) == -1, msgget, exit(1));
	printf("msgid = %d\n", msgid);

	system("ipcs -q");

	return 0;
}
