/*************************************************************************
	> File Name: threadexit.c
	> Author: duqinglong
	> Mail: du_303412@163.com 
	> Created Time: 2016年03月18日 星期五 10时15分56秒
 ************************************************************************/

#include "../apue.h"
#include <pthread.h>

#define ERROR(m)	\
	do{perror(m);exit(EXIT_FAILURE);}while(0)

void *thr_fn1(void *arg)
{
	printf("thread 1 returning\n");
	return ((void *)1);
}

void *thr_fn2(void *arg)
{
	printf("thread 2 returning\n");
	return ((void *)2);
}

int main()
{
	int			err;
	pthread_t	tid1, tid2;
	void		*tret;

	err = pthread_create(&tid1, NULL, thr_fn1, NULL);
	if (err != 0)
		ERROR("cant create thread 1");
	err = pthread_create(&tid2, NULL, thr_fn2, NULL);
	if (err != 0)
		ERROR("cant create thread 2");

	err = pthread_join(tid1, &tret);
	if (err != 0)
		ERROR("pthread 1 join error");
	printf("thread 1 exit code %ld\n", (long)tret);

	err = pthread_join(tid2, &tret);
	if (err != 0)
		ERROR("pthread 2 join error");
	printf("thread 2 exit code %ld\n", (long)tret);
	exit(0);
}
