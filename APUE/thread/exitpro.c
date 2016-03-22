/*************************************************************************
	> File Name: exitpro.c
	> Author: duqinglong
	> Mail: du_303412@163.com 
	> Created Time: 2016年03月18日 星期五 10时37分34秒
 ************************************************************************/

//在调用线程的栈上分配了结构，那么其他的线程在使用这个结构时内存的内容可能已经变了

#include "../apue.h"
#include <pthread.h>

#define ERROR(m)	\
	do{perror(m);exit(EXIT_FAILURE);}while(0)

struct foo {
	int a, b, c, d;
};

void printfoo(const char *s, const struct foo *fp)
{
	printf("%s", s);
	printf(" struct at 0x%lx\n", (unsigned long)fp);
	printf(" foo.a = %d\n", fp->a);
	printf(" foo.b = %d\n", fp->b);
	printf(" foo.c = %d\n", fp->c);
	printf(" foo.d = %d\n", fp->d);
}

void *thr_fn1(void *arg)
{
	struct foo foo = {1, 2, 3, 4};

	printfoo("thread 1:\n", &foo);
	pthread_exit((void *)&foo);
}

void *thr_fn2(void *arg)
{
	printf("thread 2: ID is %lu\n", (unsigned long)pthread_self());
	pthread_exit((void *)0);
}

int main()
{
	int			err;
	pthread_t	tid1, tid2;
	struct foo	*fp;

	if ((err = pthread_create(&tid1, NULL, thr_fn1, NULL)) != 0)
		ERROR("create thread 1 error");

	if ((err = pthread_join(tid1, (void *)&fp)) != 0)
		ERROR("join thread 1 error");
	
	sleep(1);
	printf("parent starting second thread\n");

	if ((err = pthread_create(&tid2, NULL, thr_fn2, NULL)) != 0)
		ERROR("create thread 2 error");
	sleep(1);
	printfoo("parent:\n", fp);
	exit(0);
}
