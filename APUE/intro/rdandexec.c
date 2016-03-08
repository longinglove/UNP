/*************************************************************************
    > File Name: rdandexec.c
    > Author: duqinglong
    > Mail: du_303412@163.com 
    > Created Time: Mon 07 Mar 2016 09:42:26 PM CST
 ************************************************************************/

#include"../apue.h"
#include <sys/wait.h>

int main()
{
	char	buf[MAXLINE];
	pid_t	pid;
	int		status;

	printf("%% ");
	while (fgets(buf, MAXLINE, stdin) != NULL)
	{
		if (buf[strlen(buf)-1] == '\n')
			buf[strlen(buf)-1] = 0;
		if ((pid = fork()) < 0)
		{
			printf("fork error\n");
		}
		else if (pid == 0)
		{
			execlp(buf, buf, (char *)0);
			printf("couldnt execute: %s", buf);
			exit(127);
		}

		if ((pid = waitpid(pid, &status, 0)) < 0)
			printf("waitpid error\n");
		printf("%% ");
	}
	exit(0);
}

