/*************************************************************************
	> File Name: pipe2.c
	> Author: duqinglong
	> Mail: du_303412@163.com 
	> Created Time: 2016年03月24日 星期四 17时20分46秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<unistd.h>

int main()
{
	int pfds[2];
	char buf[30];

	if (pipe(pfds) == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}

	printf("writing to file descriptor #%d\n", pfds[1]);
	write(pfds[1], "test", 5);
	printf("reading from file descriptor #%d\n", pfds[0]);
	read(pfds[0], buf, 5);
	printf("read \"%s\"\n", buf);
	exit(0);
}
