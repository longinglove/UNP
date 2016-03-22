/*************************************************************************
	> File Name: testexec.c
	> Author: duqinglong
	> Mail: du_303412@163.com 
	> Created Time: 2016年03月15日 星期二 10时54分59秒
 ************************************************************************/

#include "../apue.h"

#define ERROR(m)	\
	do {perror(m); exit(EXIT_FAILURE);} while (0)

char *env_init[] = {"USER=unknown", "PATH=/tmp", NULL};

int main()
{
	pid_t	pid;

	if ((pid = fork()) < 0)
		ERROR("fork error");
	else if (pid == 0)
		if (execle("/home/sar/bin/echoall", "echoall", "myarg1", "MY ARG2", (char*)0, env_init) < 0)
			ERROR("execle error");
	if (waitpid(pid, NULL, 0) < 0)
		ERROR("waitpid error");

	if ((pid = fork()) < 0)
		ERROR("fork error");
	else if (pid == 0)
		if (execlp("echoall", "echoall", "only 1 arg", (char*)0) < 0)
			ERROR("execlp error");
	exit(0);
}
