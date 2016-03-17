/*************************************************************************
	> File Name: sig_cld.c
	> Author: duqinglong
	> Mail: du_303412@163.com 
	> Created Time: 2016年03月17日 星期四 11时03分13秒
 ************************************************************************/

//编译运行一切正常,现在的linux都提供了可靠地信号机制

#include "../apue.h"
#include <sys/wait.h>

#define ERROR(m)	\
	do{perror(m); exit(EXIT_FAILURE);} while (0)

static void sig_cld(int);

int main()
{
	pid_t	pid;

	if (signal(SIGCLD, sig_cld) == SIG_ERR)
		ERROR("signal error");
	if ((pid = fork()) < 0)
		ERROR("fork error");
	else if (pid == 0)
	{
		sleep(2);
		_exit(0);
	}
	pause();
	exit(0);
}

static void sig_cld(int signo)
{
	pid_t	pid;
	int		status;

	printf("SIGCLD received\n");

	if (signal(SIGCLD, sig_cld) == SIG_ERR)
		ERROR("signal error");
	if ((pid = wait(&status)) < 0)
		ERROR("wait error");
	printf("pid = %d\n", pid);
}
