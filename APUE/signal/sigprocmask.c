/*************************************************************************
	> File Name: sigprocmask.c
	> Author: duqinglong
	> Mail: du_303412@163.com 
	> Created Time: 2016年03月17日 星期四 16时01分27秒
 ************************************************************************/

#include<stdio.h>
#include"../apue.h"

#define ERROR(m)	\
	do{perror(m);exit(EXIT_FAILURE);}while(0)

static void sig_quit(int);

int main()
{
	sigset_t newmask, oldmask, pendmask;

	if (signal(SIGQUIT, sig_quit) == SIG_ERR)
		ERROR("signal error");

	sigemptyset(&newmask);
	sigaddset(&newmask, SIGQUIT);
	if (sigprocmask(SIG_BLOCK, &newmask, &oldmask) < 0)
		ERROR("SIG_BLOCK error");

	sleep(5);

	if (sigpending(&pendmask) < 0)
		ERROR("sigpending error");
	if (sigismember(&pendmask, SIGQUIT))
		printf("\nSIGQUIT pending\n");

	if (sigprocmask(SIG_SETMASK, &oldmask, NULL) < 0)
		ERROR("sigprocmask error");
	printf("SIGQUIT unblocked\n");

	sleep(5);
	exit(0);
}

static void sig_quit(int signo)
{
	printf("caught SIGQUIT\n");
	if (signal(SIGQUIT, SIG_DFL) == SIG_ERR)
		ERROR("signal error");
}
