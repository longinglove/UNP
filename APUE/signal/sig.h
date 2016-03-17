/*************************************************************************
	> File Name: sig.h
	> Author: duqinglong
	> Mail: du_303412@163.com 
	> Created Time: 2016年03月17日 星期四 17时06分22秒
 ************************************************************************/

#ifndef _SIG_H_
#define _SIG_H_

#include "../apue.h"
#include<setjmp.h>
#include<time.h>
#include<errno.h>

#define ERROR(m)	\
	do{perror(m);exit(EXIT_FAILURE);}while (0)

Sigfunc *signal(int signo, Sigfunc *func); 
void pr_mask(const char *str);
void abort();
int system(const char *cmdstring);

#endif
