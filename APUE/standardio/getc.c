/*************************************************************************
	> File Name: getc.c
	> Author: duqinglong
	> Mail: du_303412@163.com 
	> Created Time: 2016年03月11日 星期五 10时10分40秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>

int main()
{
	int c;
	while ((c = getc(stdin)) != EOF)
		if (putc(c, stdout) == EOF)
			printf("output error");

	if (ferror(stdin))
		printf("input error");
	return 0;
}
