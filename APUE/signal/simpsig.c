/*************************************************************************
	> File Name: simpsig.c
	> Author: duqinglong
	> Mail: du_303412@163.com 
	> Created Time: 2016年03月16日 星期三 18时01分35秒
 ************************************************************************/

#include "../apue.h"
#include<signal.h>

#define ERROR(m)	\
	do {perror(m); exit(EXIT_FAILURE);} while (0)

static void sig_usr(int);

int main()
{
	if (signal(SIGUSR1, sig_usr) == SIG_ERR)
		ERROR("cant catch SIGUSR1");
	if (signal(SIGUSR2, sig_usr) == SIG_ERR)
		ERROR("cant catch SIGUSR2");
	for ( ; ; )
		pause();
}

static void sig_usr(int signo)
{
	if (signo == SIGUSR1)
		printf("received SIGUSR1\n");
	else if (signo == SIGUSR2)
		printf("received SIGUSR2\n");
	else
		printf("other SIG\n");
}
