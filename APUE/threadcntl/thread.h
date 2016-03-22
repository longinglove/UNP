/*************************************************************************
	> File Name: thread.h
	> Author: duqinglong
	> Mail: du_303412@163.com 
	> Created Time: 2016年03月22日 星期二 09时49分40秒
 ************************************************************************/

#ifndef _THREAD_H_
#define _THREAD_H_

#include "../apue.h"
#include <pthread.h>

#define MAXSTRINGSZ	4096
char buf[MAXSTRINGSZ];
char **environ;

int makethread(void *(*fn)(void *), void *arg);
char *getenv(const char *name);

#endif
