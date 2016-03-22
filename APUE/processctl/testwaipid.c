/*************************************************************************
	> File Name: testwaipid.c
	> Author: duqinglong
	> Mail: du_303412@163.com 
	> Created Time: 2016年03月15日 星期二 09时48分40秒
 ************************************************************************/

#include"../apue.h"
#include<sys/wait.h>

#define ERROR(m)	\
	do {perror(m); exit(EXIT_FAILURE);} while (0)

int main()
{
	pid_t	pid;

	if ((pid = fork()) < 0)
		ERROR("fork error");
	else if (pid == 0)
	{
		if ((pid = fork()) < 0)
			ERROR("fork error");
		else if (pid > 0)
			exit(0);
		sleep(2);
		printf("second child, parent pid = %ld\n", (long)getppid());
		exit(0);
	}
	if (waitpid(pid, NULL, 0) != pid)
		ERROR("waipid error");
	exit(0);
}
