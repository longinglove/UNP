/*************************************************************************
	> File Name: mutex.c
	> Author: duqinglong
	> Mail: du_303412@163.com 
	> Created Time: 2016年03月22日 星期二 10时54分46秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t	cond = PTHREAD_COND_INITIALIZER;

void *thread1(void *);
void *thread2(void *);

int i = 1;

int main()
{
	pthread_t	t_a;
	pthread_t	t_b;
	pthread_create(&t_a, NULL, thread1, (void *)NULL);
	pthread_create(&t_b, NULL, thread2, (void *)NULL);
	pthread_join(t_a, NULL);
	pthread_join(t_b, NULL);
	pthread_mutex_destroy(&mutex);
	pthread_cond_destroy(&cond);
	exit(0);
}

void *thread1(void *junk)
{
	for (i = 1; i <= 6; i++)
	{
		pthread_mutex_lock(&mutex);
		printf("thread1: lock %d\n", __LINE__);
		if (i%3 == 0)
		{
			printf("thread1:signal 1 %d\n", __LINE__);
			pthread_cond_signal(&cond);
			printf("thread1:signal 2 %d\n", __LINE__);
			sleep(1);
		}
		pthread_mutex_unlock(&mutex);
		printf("thread1: unlock %d\n\n", __LINE__);
		sleep(1);
	}
}

void *thread2(void *junk)
{
	while (i < 6)
	{
		pthread_mutex_lock(&mutex);
		printf("thread2:lock %d\n", __LINE__);
		if (i%3 != 0)
		{
			printf("thread2:wait1 %d\n", __LINE__);
			pthread_cond_wait(&cond, &mutex);
			printf("thread2:wait2 %d\n", __LINE__);
		}
		pthread_mutex_unlock(&mutex);
		printf("thread: unlock %d\n\n", __LINE__);
		sleep(1);
	}
}
