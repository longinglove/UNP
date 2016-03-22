/*************************************************************************
	> File Name: racecond.c
	> Author: duqinglong
	> Mail: du_303412@163.com 
	> Created Time: 2016年03月15日 星期二 10时23分59秒
 ************************************************************************/

#include"../apue.h"

#define ERROR(m)	\
	do {perror(m); exit(EXIT_FAILURE);} while (0)

static void charatatime(char *);

int main()
{
	pid_t	pid;

	if ((pid = fork()) < 0)
		ERROR("fork error");
	else if (pid == 0)
	{
		charatatime("output from child\n");
	}
	else
	{
		charatatime("output from parent\n");
	}
	exit(0);
}

static void charatatime(char *str)
{
	char	*ptr;
	int		c;

	setbuf(stdout, NULL);
	for (ptr = str; (c = *ptr++) != 0; )
		putc(c, stdout);
}
