/*************************************************************************
	> File Name: sigset.c
	> Author: duqinglong
	> Mail: du_303412@163.com 
	> Created Time: 2016年03月17日 星期四 15时47分47秒
 ************************************************************************/

#include<stdio.h>
#include"../apue.h"

#define ERROR(m)	\
	do{perror(m);exit(EXIT_FAILURE);}while(0)

#define sigemptyset(ptr)	(*(ptr) = 0)
#define sigfillset(ptr)		(*(ptr) = ~(sigset_t)0, 0)

#define SIGBAD(signo)	 ((signo) <= 0 || (signo) >= NSIG)

int sigaddset(sigset_t *set, int signo)
{
	if (SIGBAD(signo))
	{
		errno = EINVAL;
		return -1;
	}
	*set |= 1<<(signo-1);
	return 0;
}

int sigdelset(sigset_t *set, int signo)
{
	if (SIGBAD(signo))
	{
		errno = EINVAL;
		return -1;
	}
	*set &= ~(1<<(signo-1));
	return 0;
}

int sigismember(const sigset_t *set, int signo)
{
	if (SIGBAD(signo))
	{
		errno = EINVAL;
		return -1;
	}
	return ((*set & (1<<(signo-1))) != 0);
}
