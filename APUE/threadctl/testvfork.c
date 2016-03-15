/*************************************************************************
	> File Name: testvfork.c
	> Author: duqinglong
	> Mail: du_303412@163.com 
	> Created Time: 2016年03月14日 星期一 15时21分26秒
 ************************************************************************/

#include "../apue.h"

#define ERROR(m)	\
	do {perror(m); exit(EXIT_FAILURE);} while (0)

int		globvar = 6;

int main()
{
	int		var;
	pid_t	pid;

	var = 88;
	printf("before vfork\n");
	if ((pid = vfork()) < 0)
		ERROR("fork error");
	else if (pid == 0)
	{
		var++;
		globvar++;
		_exit(0);			//不执行标准I/O缓冲区的冲洗操作
	}
	printf("pid = %ld, globvar = %d, var = %d\n", (long)getpid(), globvar, var);
	exit(0);
}
