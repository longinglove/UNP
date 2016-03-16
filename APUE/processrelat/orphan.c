/*************************************************************************
	> File Name: orphan.c
	> Author: duqinglong
	> Mail: du_303412@163.com 
	> Created Time: 2016年03月16日 星期三 17时28分52秒
 ************************************************************************/

#include "../apue.h"
#include<errno.h>

#define ERROR(m)	\
	do {perror(m);exit(EXIT_FAILURE);} while (0)

static void sig_hup(int);
static void pr_ids(char *);

int main()
{
	char	c;
	pid_t	pid;

	pr_ids("parent");
	if ((pid = fork()) < 0)
		ERROR("fork error");
	else if (pid > 0)
		sleep(5);
	else
	{
		pr_ids("child");
		signal(SIGHUP, sig_hup);
		kill(getpid(), SIGTSTP);
		pr_ids("child");
		if (read(STDIN_FILENO, &c, 1) != 1)
			printf("read error %d on controlling TTY\n", errno);
	}
	exit(0);
}

static void sig_hup(int signo)
{
	printf("SIGHUP received, pid = %ld\n", (long)getpid());
}

static void pr_ids(char *name)
{
	printf("%s: pid = %ld, ppid = %ld, pgrp = %ld, tpgrp = %ld\n", name, (long)getpid(), (long)getppid(), (long)getpgrp(), (long)tcgetpgrp(STDIN_FILENO));
	fflush(stdout);
}
