/*************************************************************************
	> File Name: sleep3.c
	> Author: duqinglong
	> Mail: du_303412@163.com 
	> Created Time: 2016年03月17日 星期四 20时00分52秒
 ************************************************************************/

#include "../apue.h"

static void sig_alrm(int signo)
{
}

unsigned int sleep(unsigned int seconds)
{
	struct sigaction	newact, oldact;
	sigset_t			newmask, oldmask, suspmask;
	unsigned int		unslept;

	newact.sa_handler = sig_alrm;
	sigemptyset(&newact.sa_mask);
	newact.sa_flags = 0;
	sigaction(SIGALRM, &newact, &oldact);

	sigemptyset(&newmask);
	sigaddset(&newmask, SIGALRM);
	sigprocmask(SIG_BLOCK, &newmask, &oldmask);

	alarm(seconds);
	suspmask = oldmask;

	sigdelset(&suspmask, SIGALRM);
	sigsuspend(&suspmask);

	unslept = alarm(0);

	sigaction(SIGALRM, &oldact, NULL);

	sigprocmask(SIG_SETMASK, &oldmask, NULL);
	return(unslept);
}
