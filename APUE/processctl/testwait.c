/*************************************************************************
	> File Name: testwait.c
	> Author: duqinglong
	> Mail: du_303412@163.com 
	> Created Time: 2016年03月15日 星期二 10时08分11秒
 ************************************************************************/

#include"../apue.h"

#define ERROR(m)	\
	do{perror(m); exit(EXIT_FAILURE);} while (0)

int main()
{
	pid_t	pid, pc;
	int status;

	if ((pid = fork()) < 0)
		ERROR("fork error");
	else if (pid == 0)
	{
		printf("I am the child process:%ld\n", (long)getpid());
		sleep(2);
		exit(0);
	}
	if ((pc = wait(&status)) < 0)
		ERROR("wait error");
	printf("I catch the process:%ld\n", (long)pc);
	exit(0);
}
