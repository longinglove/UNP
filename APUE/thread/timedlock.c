/*************************************************************************
	> File Name: timedlock.c
	> Author: duqinglong
	> Mail: du_303412@163.com 
	> Created Time: 2016年03月21日 星期一 16时40分58秒
 ************************************************************************/

#include"../apue.h"
#include<pthread.h>

int main()
{
	int				err;
	struct timespec	tout;
	struct tm *tmp;
	char buf[64];
	pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

	pthread_mutex_lock(&lock);
	printf("mutex is locked\n");
	clock_gettime(CLOCK_REALTIME, &tout);
	tmp = localtime(&tout.tv_sec);
	strftime(buf, sizeof(buf), "%r", tmp);
	printf("current time is %s\n", buf);
	tout.tv_sec += 10;

	err = pthread_mutex_timedlock(&lock, &tout);
	clock_gettime(CLOCK_REALTIME, &tout);
	tmp = localtime(&tout.tv_sec);
	strftime(buf, sizeof(buf), "%r", tmp);
	printf("the time is now %s\n", buf);
	if (err == 0)
		printf("mutex locked again!\n");
	else
		printf("cant lock mvtex again:%s\n", strerror(err));
	exit(0);
}
