/*************************************************************************
	> File Name: alarm.c
	> Author: duqinglong
	> Mail: du_303412@163.com 
	> Created Time: 2016年03月17日 星期四 15时28分29秒
 ************************************************************************/

//alarm用于对可能阻塞的操作设置时间上限值，但是read系统调用会自动重启动，并不会有效
#include<stdio.h>
#include "../apue.h"

#define ERROR(m)	\
	do {perror(m);exit(EXIT_FAILURE);} while (0)

static void sig_alrm(int);

int main()
{
	int		n;
	char	line[MAXLINE];

	if (signal(SIGALRM, sig_alrm) == SIG_ERR)
		ERROR("signal error");
	alarm(10);
	if ((n = read(STDIN_FILENO, line, MAXLINE)) < 0)
		ERROR("read error");
	alarm(0);
	write(STDOUT_FILENO, line, n);
	exit(0);
}

static void sig_alrm(int signo)
{
}
