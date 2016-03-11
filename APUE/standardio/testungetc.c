/*************************************************************************
	> File Name: testungetc.c
	> Author: duqinglong
	> Mail: du_303412@163.com 
	> Created Time: 2016年03月11日 星期五 09时58分01秒
 ************************************************************************/

#include "../apue.h"

int main()
{
	char c;
	c = getchar();
	printf("%c\n", c);
	ungetc(c, stdin);
	c = getchar();
	printf("%c\n", c);
	return 0;
}
