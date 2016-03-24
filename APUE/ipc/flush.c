/*************************************************************************
	> File Name: flush.c
	> Author: duqinglong
	> Mail: du_303412@163.com 
	> Created Time: 2016年03月24日 星期四 11时09分09秒
 ************************************************************************/

#include"../apue.h"
#include<ctype.h>

#define ERROR(m)	\
	do{perror(m);exit(EXIT_FAILURE);}while(0)

int main()
{
	int		c;
	while ((c = getchar()) != EOF)
	{
		if (isupper(c))
			c = tolower(c);
		if (putchar(c) == EOF)
			ERROR("output error");
		if (c == '\n')
			fflush(stdout);
	}
	exit(0);
}
