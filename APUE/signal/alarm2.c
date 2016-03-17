/*************************************************************************
	> File Name: alarm2.c
	> Author: duqinglong
	> Mail: du_303412@163.com 
	> Created Time: 2016年03月17日 星期四 15时36分20秒
 ************************************************************************/

//用setjmp和longjmp实现对输入时间的上限

#include<stdio.h>
#include"../apue.h"
#include<setjmp.h>

#define ERROR(m)	\
	do {perror(m);exit(EXIT_FAILURE);}while (0)

static void sig_alrm(int);
static jmp_buf	env_alrm;

int main()
{
	int		n;
	char	line[MAXLINE];

	if (signal(SIGALRM, sig_alrm) == SIG_ERR)
		ERROR("signal error");
	if (setjmp(env_alrm) != 0)
		ERROR("read timeout");
	alarm(5);
	if ((n = read(STDIN_FILENO, line, MAXLINE)) < 0)
		ERROR("read error");
	alarm(0);
	write(STDOUT_FILENO, line, n);
	exit(0);
}

static void sig_alrm(int signo)
{
	longjmp(env_alrm, 1);
}
