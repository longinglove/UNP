/*************************************************************************
	> File Name: thread.c
	> Author: duqinglong
	> Mail: du_303412@163.com 
	> Created Time: 2016年03月22日 星期二 09时50分48秒
 ************************************************************************/

#include "thread.h"

pthread_mutex_t	env_mutex;
pthread_once_t init_done = PTHREAD_ONCE_INIT;

//以分离状态创建线程
int makethread(void *(*fn)(void *), void *arg)
{
	int				err;
	pthread_t		tid;
	pthread_attr_t	attr;

	err = pthread_attr_init(&attr);
	if (err != 0)
		return (err);
	err = pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
	if (err == 0)
		err = pthread_create(&tid, &atr, fn, arg);
	pthread_attr_destroy(&attr);
	return (err);
}

//getenv的一个实现，不可重入
char *getenv(const *name)
{
	int i, len;
	len = strlen(name);
	for (i = 0; environ[i] != NULL; i++)
	{
		if ((strncmp(name, environ[i], len) == 0) && (environ[i][len] == '='))
		{
			strncpy(envbuf, &environ[i][len+1], MAXSTRINGSZ-1);
			return(envbuf);
		}
	}
	return (NULL);
}

//getenv的可重入版本（线程安全）pthread_once函数确保不管多少线程同时竞争，每个进程只调用thread_init函数一次
static void thread_init(void)
{
	pthread_mutexattr_t	attr;

	pthread_mutexattr_init(&attr);
	pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE);
	pthread_mutex_init(&env_mutex, &attr);
	pthread_mutexattr_destroy(&attr);
}

int getenv_r(const char *name, char *buf, int buflen)
{
	int i, len, olen;

	pthread_once(&init_done, thread_init);
	len = strlen(name);
	pthread_mutex_lock(&env_mutex);
	for (i = 0; environ[i] != NULL; i++)
	{
		if ((strncmp(name, environ[i], len) == 0) && (environ[i][len]) == '=')
		{
			olen = strlen(&environ[i][len+1]);
			if (olen >= len)
			{
				pthread_mutex_unlock(&env_mutex);
				return (ENOSPC);
			}
			strcpy(buf, &environ[i][len+1]);
			pthread_mutex_unlock(&env_mutex);
			return 0;
		}
	}
	pthread_mutex_unlock(&env_mutex);
	return (ENOENT);
}
