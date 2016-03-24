/*************************************************************************
	> File Name: flushpopen.c
	> Author: duqinglong
	> Mail: du_303412@163.com 
	> Created Time: 2016年03月24日 星期四 11时11分57秒
 ************************************************************************/

#include "../apue.h"
#include <sys/wait.h>

#define ERROR(m)	\
	do{perror(m);exit(EXIT_FAILURE);}while(0)

int main()
{
	char	line[MAXLINE];
	FILE	*fpin;

	if ((fpin = popen("~/UNP/APUE/ipc/myuclc", "r")) == NULL)
		ERROR("popen error");
	for ( ; ; )
	{
		fputs("prompt> ", stdout);
		fflush(stdout);
		if (fgets(line, MAXLINE, fpin) == NULL)
			break;
		if (fputs(line, stdout) == EOF)
			ERROR("fputs error");
	}
	if (pclose(fpin) == -1)
		ERROR("pclose error");
	putchar('\n');
	exit(0);
}
