/*************************************************************************
	> File Name: pthreadclean.c
	> Author: duqinglong
	> Mail: du_303412@163.com 
	> Created Time: 2016年03月18日 星期五 11时03分11秒
 ************************************************************************/

#include "../apue.h"
#include <pthread.h>

#define ERROR(m)	\
	do{perror(m);exit(EXIT_FAILURE);}while(0)

void cleanup(void *arg)
{
	printf("cleanup: %s\n", (char *)arg);
}

void *thr_fn1(void *arg)
{
	printf("thread 1 start\n");
	pthread_cleanup_push(cleanup, "thread 1 first handler");
	pthread_cleanup_push(cleanup, "thread 1 second handler");
	printf("thread 1 push complete\n");
	if (arg)
		return ((void*)1);
	pthread_cleanup_pop(0);
	pthread_cleanup_pop(0);
	return((void *)1);
}

void *thr_fn2(void *arg)
{
	printf("thread 2 start\n");
	pthread_cleanup_push(cleanup, "thread 2 first handler");
	pthread_cleanup_push(cleanup, "thread 2 second handler");
	printf("thread 2 push complete\n");
	if (arg)
		pthread_exit((void*)2);
	pthread_cleanup_pop(0);
	pthread_cleanup_pop(0);
	pthread_exit((void*)2);
}

int main()
{
	int			err;
	pthread_t	tid1, tid2;
	void		*tret;

	if ((err = pthread_create(&tid1, NULL, thr_fn1, (void *)1)) != 0)
		ERROR("cant create thread 1");
	if ((err = pthread_create(&tid2, NULL, thr_fn2, (void *)1)) != 0)
		ERROR("cant create thread 2");

	if ((err = pthread_join(tid1, &tret)) != 0)
		ERROR("cant join with thread 1");
	printf("thread1 exit code %ld\n", (long)tret);

	if ((err = pthread_join(tid2, &tret)) != 0)
		ERROR("cant join with thread 2");
	printf("thread2 exit code %ld\n", (long)tret);
	exit(0);
}
