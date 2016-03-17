/*************************************************************************
	> File Name: sigsuspend.c
	> Author: duqinglong
	> Mail: du_303412@163.com 
	> Created Time: 2016年03月17日 星期四 17时42分42秒
 ************************************************************************/

#include "sig.h"

static void sig_int(int);

int main()
{
	sigset_t	newmask, oldmask, waitmask;

	pr_mask("program start: ");

	if (signal(SIGINT, sig_int) == SIG_ERR)
		ERROR("signal error");

	sigemptyset(&waitmask);
	sigaddset(&waitmask, SIGUSR1);
	sigemptyset(&newmask);
	sigaddset(&newmask, SIGINT);

	if (sigprocmask(SIG_BLOCK, &newmask, &oldmask) < 0)
		ERROR("sigprocmask error");
	pr_mask("in critical region: ");

	if (sigsuspend(&waitmask) != -1)
		ERROR("sigsuspend error");
	pr_mask("after return from sigsuspend: ");

	if (sigprocmask(SIG_SETMASK, &oldmask, NULL) < 0)
		ERROR("sigprocmask error");
	pr_mask("program exit: ");

	exit(0);
}

static void sig_int(int signo)
{
	pr_mask("\nin sig_int: ");
}
