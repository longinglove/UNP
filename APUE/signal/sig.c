/*************************************************************************
	> File Name: sig.c
	> Author: duqinglong
	> Mail: du_303412@163.com 
	> Created Time: 2016年03月17日 星期四 17时08分11秒
 ************************************************************************/

#include"sig.h"

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

void pr_mask(const char *str)
{
	sigset_t	sigset;
	int			errno_save;

	errno_save = errno;
	if (sigprocmask(0, NULL, &sigset) < 0)
		ERROR("sigprocmask error");
	else
	{
		printf("%s", str);
		if (sigismember(&sigset, SIGINT))
			printf(" SIGINT");
		if (sigismember(&sigset, SIGQUIT))
			printf(" SIGQUIT");
		if (sigismember(&sigset, SIGUSR1))
			printf(" SIGUSR1");
		if (sigismember(&sigset, SIGALRM))
			printf(" SIGALRM");

		printf("\n");
	}
	errno = errno_save;
}

void abort()
{
	sigset_t	mask;
	struct sigaction action;

	sigaction(SIGABRT, NULL, &action);
	if (action.sa_handler == SIG_IGN)
	{
		action.sa_handler = SIG_DFL;
		sigaction(SIGABRT, &action, NULL);
	}
	if (action.sa_handler == SIG_DFL)
		fflush(NULL);
	sigfillset(&mask);
	sigdelset(&mask, SIGABRT);
	sigprocmask(SIG_SETMASK, &mask, NULL);
	kill(getpid(), SIGABRT);

	fflush(NULL);
	action.sa_handler = SIG_DFL;
	sigaction(SIGABRT, &action, NULL);
	sigprocmask(SIG_SETMASK, &mask, NULL);
	kill(getpid(), SIGABRT);
	exit(1);
}

int system(const char *cmdstring)
{
	pid_t		pid;
	int			status;
	struct sigaction ignore, saveintr, savequit;
	sigset_t	chldmask, savemask;

	if (cmdstring == NULL)
		return 1;

	ignore.sa_handler = SIG_IGN;
	sigemptyset(&ignore.sa_mask);
	ignore.sa_flags = 0;
	if (sigaction(SIGINT, &ignore, &saveintr) < 0)
		return -1;
	if (sigaction(SIGQUIT, &ignore, &savequit) < 0)
		return -1;
	sigemptyset(&chldmask);
	sigaddset(&chldmask, SIGCHLD);
	if (sigprocmask(SIG_BLOCK, &chldmask, &savemask) < 0)
		return -1;

	if ((pid = fork()) < 0)
		status = -1;
	else if (pid == 0)
	{
		sigaction(SIGINT, &saveintr, NULL);
		sigaction(SIGQUIT, &savequit, NULL);
		execl("/bin/sh", "sh", "-c", cmdstring, (char *)0);
		_exit(127);
	}
	else
	{
		while (waitpid(pid, &status, 0) < 0)
		{
			if (errno != EINTR)
			{
				status = -1;
				break;
			}
		}
	}

	if (sigaction(SIGINT, &saveintr, NULL) < 0)
		return -1;
	if (sigaction(SIGQUIT, &savequit, NULL) < 0)
		return -1;
	if (sigprocmask(SIG_SETMASK, &savemask, NULL) < 0)
		return -1;
	return status;
}
