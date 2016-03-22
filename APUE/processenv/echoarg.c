/*************************************************************************
	> File Name: echoarg.c
	> Author: duqinglong
	> Mail: du_303412@163.com 
	> Created Time: 2016年03月14日 星期一 10时15分03秒
 ************************************************************************/

#include "../apue.h"

int main(int argc, char *argv[])
{
	int i;
	for (i = 0; argv[i] != NULL; i++)
		printf("argv[%d]: %s\n", i, argv[i]);
	return 0;
}
