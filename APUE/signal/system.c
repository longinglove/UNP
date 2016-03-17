/*************************************************************************
	> File Name: system.c
	> Author: duqinglong
	> Mail: du_303412@163.com 
	> Created Time: 2016年03月17日 星期四 19时28分05秒
 ************************************************************************/

#include "sig.h"
#include<stdio.h>

static void sig_int(int signo);
static void sig_chld(int signo);

int main()
{
	if (signal(SIGINT, sig_int) == SIG_ERR)
		ERROR("signal SIGINT error");
	if (signal(SIGCHLD, sig_chld) == SIG_ERR)
		ERROR("signal SIGCHLD error");
	if (system("/bin/ed") < 0)
		ERROR("system error");
	exit(0);
}

static void sig_int(int signo)
{
	printf("caught SIGINT\n");
}

static void sig_chld(int signo)
{
	printf("caught SIGCHLD\n");
}
