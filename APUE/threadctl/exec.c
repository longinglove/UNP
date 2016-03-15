/*************************************************************************
	> File Name: exec.c
	> Author: duqinglong
	> Mail: du_303412@163.com 
	> Created Time: 2016年03月15日 星期二 15时14分37秒
 ************************************************************************/

#include "../apue.h"

#define ERROR(m)	\
	do{perror(m); exit(EXIT_FAILURE);} while (0)

int main()
{
	pid_t	pid;
	if ((pid = fork()) < 0)
		ERROR("fork error");
	else if (pid == 0)
		if (execl("/home/silence/UNP/APUE/threadctl/testinterp", "testinterp", "myarg1", "myarg2", (char *)0) < 0)
			ERROR("execl error");
	if (waitpid(pid, NULL, 0) < 0)
		ERROR("waipid error");
	return 0;
}
