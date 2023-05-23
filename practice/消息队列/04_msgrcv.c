#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <share.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>


typedef struct {
	long mtype;
	char mtext[128];
}MSG;

#define TEXTSIZE (sizeof(MSG) - sizeof(long))

int main(int argc, char const *argv[])
{
	key_t mykey;
	ERRP((mykey = ftok(".", 100)) == -1, ftok, exit(1));
	printf("mykey = %#x\n", mykey);

	int msgid;
	ERRP(-1 == (msgid = msgget(mykey, IPC_CREAT|0666)), msgget, exit(1));
	printf("msgid = %d\n", msgid);

	MSG msg;
	ERRP(-1 == (msgrcv(msgid, &msg, TEXTSIZE, 0, 0)), msgrcv, exit(1));
	printf("text = %s\n", msg.mtext);

	return 0;
}
