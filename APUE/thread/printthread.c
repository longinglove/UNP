/*************************************************************************
	> File Name: printthread.c
	> Author: duqinglong
	> Mail: du_303412@163.com 
	> Created Time: 2016年03月18日 星期五 09时58分05秒
 ************************************************************************/

#include "../apue.h"
#include <pthread.h>

#define ERROR(m)	\
	do{perror(m);exit(EXIT_FAILURE);}while(0)

pthread_t	ntid;

void printids(const char *s)
{
	pid_t		pid;
	pthread_t	tid;

	pid = getpid();
	tid = pthread_self();
	printf("%s pid %lu tid %lu (0x%lx)\n", s, (unsigned long)pid, (unsigned long)tid, (unsigned long)tid);
}

void *thr_fn(void *arg)
{
	printids("new thread: ");
	return ((void*)0);
}

int main()
{
	int err;

	err = pthread_create(&ntid, NULL, thr_fn, NULL);
	if (err != 0)
		ERROR("cant create thread");
	printids("main thread:");
	sleep(1);
	exit(0);
}
