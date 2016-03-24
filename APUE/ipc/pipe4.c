/*************************************************************************
	> File Name: pipe4.c
	> Author: duqinglong
	> Mail: du_303412@163.com 
	> Created Time: 2016年03月24日 星期四 17时34分21秒
 ************************************************************************/

#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>

int main()
{
	int		pfds[2];

	pipe(pfds);

	if (!fork())
	{
		close(1);
		dup(pfds[1]);
		close(pfds[0]);
		execlp("ls", "ls", NULL);
	}
	else
	{
		close(0);
		dup(pfds[0]);
		close(pfds[1]);
		execlp("wc", "wc", "-l", NULL);
	}
	exit(0);
}
