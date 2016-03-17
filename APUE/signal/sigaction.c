/*************************************************************************
	> File Name: sigaction.c
	> Author: duqinglong
	> Mail: du_303412@163.com 
	> Created Time: 2016年03月17日 星期四 16时45分54秒
 ************************************************************************/

#include<stdio.h>
#include"../apue.h"

#define ERROR(m)	\
	do{perror(m);exit(EXIT_FAILURE);}while (0)

Sigfunc *signal(int signo, Sigfunc *func)
{
	struct sigaction act, oact;
	act.sa_handler = func;
	sigemptyset(&act.sa_mask);
	act.sa_flags = 0;
	if (signo == SIGALRM)
	{
#ifdef SA_INTERRUPT
		act.sa_flags |= SA_INTERRUPT;
#endif
	}
	else
	{
		act.sa_flags |= SA_RESTART;
	}
	if (sigaction(signo, &act, &oact) < 0)
		return (SIG_ERR);
	return (oact.sa_handler);
}

static void sig_int(int);

int main()
{
	if (signal(SIGINT, sig_int) == SIG_ERR)
		ERROR("signal error");
	pause();
	return 0;
}

static void sig_int(int signo)
{
	printf("catch SIGINT\n");
}
