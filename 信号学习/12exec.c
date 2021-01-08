#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{
	pid_t pid;
	pid = fork();
	if (pid == -1)
	{
		perror("fail to fork");
		exit(0);
	}
	else if (pid == 0)
	{
		printf("son\n");
		/*execl("/bin/ls", "ls", "-l", NULL);*/
		/*execlp("ls", "ls", "-l", NULL);*/
		/*execlp("./a.out", "./a.out", NULL);*/
		exit(1);
	}
	else
	{
		printf("father\n");
		waitpid(pid, NULL, 0);
	}

	return 0;
}
