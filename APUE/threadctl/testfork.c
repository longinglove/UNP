/*************************************************************************
	> File Name: testfork.c
	> Author: duqinglong
	> Mail: du_303412@163.com 
	> Created Time: 2016年03月14日 星期一 14时50分20秒
 ************************************************************************/

#include "../apue.h"

#define ERROR(m)	\
	do {perror(m); exit(EXIT_FAILURE);} while (0)

int			globvar = 6;
char buf[] = "a write to stdout\n";

int main()
{
	int		var;
	pid_t	pid;

	var = 88;
	if (write(STDOUT_FILENO, buf, sizeof(buf)-1) != sizeof(buf)-1)
		ERROR("write error");
	printf("before fork\n");
	if ((pid = fork()) < 0)
		ERROR("fork error");
	else if (pid == 0)
	{
		globvar++;
		var++;
	}
	else
		sleep(2);
	printf("pid = %ld, glob = %d, var = %d\n", (long)getpid(), globvar, var);
	exit(0);
}
