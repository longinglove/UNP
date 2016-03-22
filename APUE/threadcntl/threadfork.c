/*************************************************************************
	> File Name: threadfork.c
	> Author: duqinglong
	> Mail: du_303412@163.com 
	> Created Time: 2016年03月22日 星期二 15时17分52秒
 ************************************************************************/

#include "../apue.h"
#include <pthread.h>

#define ERROR(m)	\
	do{perror(m);exit(EXIT_FAILURE);}while(0)

pthread_mutex_t	lock1 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t lock2 = PTHREAD_MUTEX_INITIALIZER;

void prepare(void)
{
	int err;
	printf("preparing locks..\n");
	if ((err = pthread_mutex_lock(&lock1)) != 0)
		ERROR("lock1 prepare error");
	if ((err = pthread_mutex_lock(&lock2)) != 0)
		ERROR("lock2 prepare error");
}

void parent(void)
{
	int err;

	printf("parent unlocking locks..\n");
	if ((err = pthread_mutex_unlock(&lock1)) != 0)
		ERROR("lock1 parent error");
	if ((err = pthread_mutex_unlock(&lock2)) != 0)
		ERROR("lock2 parent error");
}

void child (void)
{
	int err;
	printf("child unlocking locks..\n");
	if ((err = pthread_mutex_unlock(&lock1)) != 0)
		ERROR("lock1 child error");
	if ((err = pthread_mutex_unlock(&lock2)) != 0)
		ERROR("lock2 child error");
}

void *thr_fn(void *arg)
{
	printf("thread started...\n");
	pause();
	return (0);
}

int main()
{
	int			err;
	pid_t		pid;
	pthread_t	tid;

	if ((err = pthread_atfork(prepare, parent, child)) != 0)
		ERROR("atfork error");

	if ((err = pthread_create(&tid, NULL, thr_fn, 0)) != 0)
		ERROR("thread create error");
	sleep(2);
	printf("parent about to fork...\n");
	if ((pid = fork()) < 0)
		ERROR("fork error");
	else if (pid == 0)
		printf("child returned from fork\n");
	else
		printf("parent returned from fork\n");
	exit(0);
}
