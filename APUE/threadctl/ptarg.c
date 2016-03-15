/*************************************************************************
	> File Name: ptarg.c
	> Author: duqinglong
	> Mail: du_303412@163.com 
	> Created Time: 2016年03月15日 星期二 15时12分40秒
 ************************************************************************/

#include "../apue.h"

int main(int argc, char *argv[])
{
	int i;
	for (i = 0; i < argc; i++)
		printf("%s\n", argv[i]);
	return 0;
}
