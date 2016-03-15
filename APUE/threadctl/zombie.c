/*************************************************************************
	> File Name: zombie.c
	> Author: duqinglong
	> Mail: du_303412@163.com 
	> Created Time: 2016年03月15日 星期二 21时14分36秒
 ************************************************************************/

#include "../apue.h"

#define PSCMD "ps -o pid,ppid,state,tty,command"

#define ERROR(m)	\
	do {perror(m); exit(EXIT_FAILURE);} while (0)

int main()
{
	pid_t	pid;

	if ((pid = fork()) < 0)
		ERROR("fork error");
	else if (pid == 0)
		exit(0);
	sleep(4);
	system(PSCMD);
	exit(0);
}
