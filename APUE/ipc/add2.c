/*************************************************************************
	> File Name: add2.c
	> Author: duqinglong
	> Mail: du_303412@163.com 
	> Created Time: 2016年03月24日 星期四 11时22分37秒
 ************************************************************************/

#include "../apue.h"

#define ERROR(m)	\
	do{perror(m);exit(EXIT_FAILURE);}while(0)

int main()
{
	int		n, int1, int2;
	char	line[MAXLINE];

	while ((n = read(STDIN_FILENO, line, MAXLINE)) > 0)
	{
		line[n] = 0;
		if ((sscanf(line, "%d%d", &int1, &int2)) == 2)
		{
			sprintf(line, "%d\n", int1+int2);
			n = strlen(line);
			if (write(STDOUT_FILENO, line, n) != n)
				ERROR("write error");
		}
		else
		{
			if (write(STDOUT_FILENO, "invalid args\n", 13) != 13)
				ERROR("write error");
		}
	}
	exit(0);
}
