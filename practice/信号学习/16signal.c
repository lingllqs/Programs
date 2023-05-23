#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>


void handler(int sig);
int main(int argc, char const *argv[])
{
    /*
	 *if (signal(SIGINT, SIG_DFL) == SIG_ERR)
	 *{
	 *    perror("fail to signal\n");
	 *    exit(1);
	 *}
	 *if (signal(SIGQUIT, SIG_DFL) == SIG_ERR)
	 *{
	 *    perror("fail to signal\n");
	 *    exit(1);
	 *}
	 *if (signal(SIGTSTP, SIG_DFL) == SIG_ERR)
	 *{
	 *    perror("fail to signal\n");
	 *    exit(1);
	 *}
     */


    /*
	 *if (signal(SIGINT, SIG_IGN) == SIG_ERR)
	 *{
	 *    perror("fail to signal");
	 *}
	 *if (signal(SIGQUIT, SIG_IGN) == SIG_ERR)
	 *{
	 *    perror("fail to signal");
	 *}
	 *if (signal(SIGTSTP, SIG_IGN) == SIG_ERR)
	 *{
	 *    perror("fail to signal");
	 *}
     */

    /*
	 *if (signal(SIGKILL, SIG_IGN) == SIG_ERR)
	 *{
	 *    perror("fail to signal");
	 *}
     */
	
	if (signal(SIGINT, handler) == SIG_ERR)
	{
		perror("fail to signal");
		exit(1);
	}
	if (signal(SIGQUIT, handler) == SIG_ERR)
	{
		perror("fail to signal");
		exit(1);
	}
	if (signal(SIGTSTP, handler) == SIG_ERR)
	{
		perror("fail to signal");
		exit(1);
	}

	while(1)
	{
		printf("hello world\n");
		sleep(1);
	}


	return 0;
}
void handler(int sig)
{
	if (sig == SIGINT)
	{
		printf("SIGINT正在处理\n");
	}
	if (sig == SIGQUIT)
	{
		printf("SIGQUIT正在处理\n");
	}
	if (sig == SIGTSTP)
	{
		printf("SIGTSTP正在处理\n");
	}
}
