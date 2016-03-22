/*************************************************************************
	> File Name: threadsig.c
	> Author: duqinglong
	> Mail: du_303412@163.com 
	> Created Time: 2016年03月22日 星期二 14时58分16秒
 ************************************************************************/

#include "../apue.h"
#include <pthread.h>

#define ERROR(m)	\
	do{perror(m);exit(EXIT_FAILURE);}while(0)

int			quitflag;
sigset_t	mask;

pthread_mutex_t	lock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t	waitloc = PTHREAD_COND_INITIALIZER;

void *thr_fn(void *arg)
{
	int err, signo;
	for ( ; ; )
	{
		if (sigwait(&mask, &signo) != 0)
			ERROR("sigwait error");
		switch (signo) {
			case SIGINT:
				printf("\ninterrupt\n");
				break;
			case SIGQUIT:
				pthread_mutex_lock(&lock);
				quitflag = 1;
				pthread_mutex_unlock(&lock);
				pthread_cond_signal(&waitloc);
				return (0);
			default:
				printf("unexpected signal %d\n", signo);
				exit(1);
		}
	}
}

int main()
{
	int			err;
	sigset_t	oldmask;
	pthread_t	tid;

	sigemptyset(&mask);
	sigaddset(&mask, SIGINT);
	sigaddset(&mask, SIGQUIT);
	if ((err = pthread_sigmask(SIG_BLOCK, &mask, &oldmask)) != 0)
		ERROR("SIG_BLOCK error");
	if (pthread_create(&tid, NULL, thr_fn, 0) != 0)
		ERROR("cant create thread");
	pthread_mutex_lock(&lock);
	while (quitflag == 0)
		pthread_cond_wait(&waitloc, &lock);
	pthread_mutex_unlock(&lock);

	quitflag = 0;

	if (sigprocmask(SIG_SETMASK, &oldmask, NULL) < 0)
		ERROR("SIG_SETMASK error");

	exit(0);
}
