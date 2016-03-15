/*************************************************************************
	> File Name: exitstat.c
	> Author: duqinglong
	> Mail: du_303412@163.com 
	> Created Time: 2016年03月15日 星期二 09时26分57秒
 ************************************************************************/

#include"../apue.h"
#include<sys/wait.h>

#define ERROR(m)	\
	do{perror(m); exit(EXIT_FAILURE);} while (0)

void pr_exit(int);

int main()
{
	pid_t	pid;
	int		status;
	if ((pid = fork()) < 0)
		ERROR("fork error");
	else if (pid == 0)
		exit(7);

	if(wait(&status) != pid)
		ERROR("wait error");
	pr_exit(status);

	if ((pid = fork()) < 0)
		ERROR("fork error");
	else if (pid == 0)
		abort();

	if (wait(&status) != pid)
		ERROR("wait error");
	pr_exit(status);

	if ((pid = fork()) < 0)
		ERROR("fork error");
	else if (pid == 0)
		status /= 0;

	if (wait(&status) != pid)
		ERROR("wait error");
	pr_exit(status);
	exit(0);
}

void pr_exit(int status)
{
	if (WIFEXITED(status))
		printf("normal termination, exit status = %d\n", WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
		printf("abnormal termination, signal number = %d%s\n", WTERMSIG(status),
#ifdef	WCOREDUMP
				WCOREDUMP(status)?" (core file generated)":"");
#else
				"");
#endif
	else if (WIFSTOPPED(status))
		printf("child stopped, signal number = %d\n", WSTOPSIG(status));
}
