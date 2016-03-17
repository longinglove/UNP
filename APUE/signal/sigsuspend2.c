/*************************************************************************
	> File Name: sigsuspend2.c
	> Author: duqinglong
	> Mail: du_303412@163.com 
	> Created Time: 2016年03月17日 星期四 17时58分39秒
 ************************************************************************/

#include "sig.h"

volatile sig_atomic_t quitflag;

static void sig_int(int);

int main()
{
	sigset_t	newmask, oldmask, zeromask;

	if (signal(SIGINT, sig_int) == SIG_ERR)
		ERROR("signal SIGINT error");
	if (signal(SIGQUIT, sig_int) == SIG_ERR)
		ERROR("signal SIGQUIT error");

	sigemptyset(&zeromask);
	sigemptyset(&newmask);
	sigaddset(&newmask, SIGQUIT);

	if (sigprocmask(SIG_BLOCK, &newmask, &oldmask) < 0)
		ERROR("sigprocmask error");

	while (quitflag == 0)
		sigsuspend(&zeromask);
	quitflag = 0;
	if (sigprocmask(SIG_SETMASK, &oldmask, NULL) < 0)
		ERROR("sigprocmask error");
	exit(0);
}

static void sig_int(int signo)
{
	if (signo == SIGINT)
		printf("\ninterrupt\n");
	else if (signo == SIGQUIT)
		quitflag = 1;
}
