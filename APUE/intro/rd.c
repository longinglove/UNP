/*************************************************************************
    > File Name: rd.c
    > Author: duqinglong
    > Mail: du_303412@163.com 
    > Created Time: Mon 07 Mar 2016 08:22:39 PM CST
 ************************************************************************/

#include"../apue.h"

#define BUFFSIZE 4096

int main()
{
	int n;
	char buf[BUFFSIZE];

	while ((n = read(STDIN_FILENO, buf, BUFFSIZE)) > 0)			//read函數返回讀的字節數
		if (write(STDOUT_FILENO, buf, n) != n)
			printf("write error");
	if (n < 0)
		printf("read error");
	return 0;
}

