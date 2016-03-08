/*************************************************************************
    > File Name: rdandexec2.c
    > Author: duqinglong
    > Mail: du_303412@163.com 
    > Created Time: Mon 07 Mar 2016 10:26:23 PM CST
 ************************************************************************/

#include"../apue.h"
#include<sys/wait.h>

static void sig_int(int);

int main()
{
	char buf[MAXLINE];
	pid_t pid;
	int status;

	if (signal(SIGINT, sig_int) == SIG_ERR)
		printf("signal error");
	printf("%% ");
	while (fgets(buf, MAXLINE, stdin) != NULL)
	{
		if (buf[strlen(buf)-1] == '\n')
			buf[strlen(buf)-1] = 0;
		if ((pid = fork()) < 0)
			printf("fork error");
		else if (pid == 0)
		{
			execlp(buf, buf, (char *)0);
			printf("couldnt execute:%s", buf);
			exit(127);
		}

		if ((pid = waitpid(pid, &status, 0)) < 0)
			printf("waitpid error");
		printf("%% ");
	}
	return 0;
}

void sig_int(int signo)
{
	printf("interrupt\n%% ");
}
