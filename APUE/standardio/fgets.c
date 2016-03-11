/*************************************************************************
	> File Name: fgets.c
	> Author: duqinglong
	> Mail: du_303412@163.com 
	> Created Time: 2016年03月11日 星期五 10时13分02秒
 ************************************************************************/

#include"../apue.h"

int main()
{
	char buf[MAXLINE];
	while (fgets(buf, MAXLINE, stdin) != NULL)
		if (fputs(buf, stdout) == EOF)
			printf("fputs error");
	if (ferror(stdin))
		printf("finput error");
	return 0;
}
