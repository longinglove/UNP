/*************************************************************************
	> File Name: sleep1.c
	> Author: duqinglong
	> Mail: du_303412@163.com 
	> Created Time: 2016年03月17日 星期四 14时37分24秒
 ************************************************************************/

#include<stdio.h>
#include "../apue.h"

static void sig_alrm(int signo)
{
	//nothing to do, just return to wake up the pause
}

unsigned int sleep1(unsigned int seconds)
{
	if (signal(SIGALRM, sig_alrm) == SIG_ERR)
		return (seconds);
	alarm(seconds);
	pause();
	return (alarm(0));
}
