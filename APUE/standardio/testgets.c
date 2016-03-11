/*************************************************************************
	> File Name: testgets.c
	> Author: duqinglong
	> Mail: du_303412@163.com 
	> Created Time: 2016年03月11日 星期五 10时05分03秒
 ************************************************************************/

#include "../apue.h"

int main()
{
	char a[100] = {0};
	fgets(a, 100, stdin);
	fputs(a, stdout);
	memset(a, 0, sizeof(a));
	gets(a);
	puts(a);
	return 0;
}
