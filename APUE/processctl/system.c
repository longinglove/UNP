/*************************************************************************
	> File Name: system.c
	> Author: duqinglong
	> Mail: du_303412@163.com 
	> Created Time: 2016年03月15日 星期二 17时23分28秒
 ************************************************************************/

#include "../apue.h"
#include<errno.h>

#define ERROR(m)	\
	do {perror(m); exit(EXIT_FAILURE);} while (0)

int system(const char*);
void pr_exit(int status);

int main()
{
	int		status;
	if ((status = system("date")) < 0)
		ERROR("system error");
	pr_exit(status);

	if ((status = system("nosuchcommand")) < 0)
		ERROR("system error");
	pr_exit(status);

	if ((status = system("who; exit 44")) < 0)
		ERROR("system error");
	pr_exit(status);
	exit(0);
}

int system(const char* cmdstring)
{
	pid_t	pid;
	int		status;

	if (cmdstring == NULL)
		return 1;
	if ((pid = fork()) < 0)
		ERROR("fork error");
	else if (pid == 0)
	{
		execl("/bin/sh", "sh", "-c", cmdstring, (char *)0);
		_exit(127);
	}
	else
	{
		while (waitpid(pid, &status, 0) < 0)
		{
			if (errno != EINTR)
			{
				status = -1;
				break;
			}
		}
	}
	return status;
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

