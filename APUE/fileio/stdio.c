/*************************************************************************
    > File Name: stdio.c
    > Author: duqinglong
    > Mail: du_303412@163.com 
    > Created Time: Tue 08 Mar 2016 03:40:47 PM CST
 ************************************************************************/

#include"../apue.h"

int main()
{
	char buf[MAXLINE];
	int n;
	while ((n = read(STDIN_FILENO, buf, MAXLINE)) > 0)
		if (write(STDOUT_FILENO, buf, n) != n)
			printf("write error");
	if (n < 0)
		printf("read error");
	return 0;
}

