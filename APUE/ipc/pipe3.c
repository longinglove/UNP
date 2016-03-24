/*************************************************************************
	> File Name: pipe3.c
	> Author: duqinglong
	> Mail: du_303412@163.com 
	> Created Time: 2016年03月24日 星期四 17时27分13秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<sys/types.h>
#include<unistd.h>

int main()
{
	int		pfds[2];
	char	buf[30];

	if (pipe(pfds) == -1)
	{
		perror("pipe error");
		exit(EXIT_FAILURE);
	}
	if (!fork())
	{
		printf(" CHILD: writing to the pipe\n");
		sleep(2);
		write(pfds[1], "test", 5);
		printf(" CHILD: exit\n");
		exit(0);
	}
	else
	{
		printf("PARENT: reading from pipe\n");
		read(pfds[0], buf, 5);
		printf("PARENT: read \"%s\"\n", buf);
		wait(NULL);
	}
	exit(0);
}

