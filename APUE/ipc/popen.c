/*************************************************************************
	> File Name: popen.c
	> Author: duqinglong
	> Mail: du_303412@163.com 
	> Created Time: 2016年03月24日 星期四 10时54分03秒
 ************************************************************************/

#include "../apue.h"
#include <sys/wait.h>

#define PAGER	"${PAGER:-more}"

#define ERROR(m)	\
	do{perror(m);exit(EXIT_FAILURE);}while(0)

int main(int argc, char *argv[])
{
	char	line[MAXLINE];
	FILE	*fpin, *fpout;

	if (argc != 2)
		ERROR("usage:input error");
	if ((fpin = fopen(argv[1], "r")) == NULL)
		ERROR("open error");
	if ((fpout = popen(PAGER, "w")) == NULL)
		ERROR("popen error");

	while (fgets(line, MAXLINE, fpin) != NULL)
	{
		if (fputs(line, fpout) == EOF)
			ERROR("fputs error");
	}
	if (ferror(fpin))
		ERROR("fgets error");
	if (pclose(fpout) == -1)
		ERROR("pclose error");
	exit(0);
}
