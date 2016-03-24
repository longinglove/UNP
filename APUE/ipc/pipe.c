/*************************************************************************
	> File Name: pipe.c
	> Author: duqinglong
	> Mail: du_303412@163.com 
	> Created Time: 2016年03月24日 星期四 10时23分30秒
 ************************************************************************/

#include "../apue.h"
#include <sys/wait.h>

#define ERROR(m)	\
	do{perror(m);exit(EXIT_FAILURE);}while(0)
#define DEF_PAGER	"/bin/more"

int main(int argc, char *argv[])
{
	int		n;
	int		fd[2];
	pid_t	pid;
	char	*pager, *argv0;
	char	line[MAXLINE];
	FILE	*fp;

	if (argc != 2)
		ERROR("usage: input error");
	if ((fp = fopen(argv[1], "r")) == NULL)
		ERROR("fopen error");
	if (pipe(fd) < 0)
		ERROR("pipe error");

	if ((pid = fork()) < 0)
		ERROR("fork error");
	else if (pid > 0)
	{
		close(fd[0]);
		while (fgets(line, MAXLINE, fp) != NULL)
		{
			n = strlen(line);
			if (write(fd[1], line, n) != n)
				ERROR("write error");
		}
		if (ferror(fp))
			ERROR("fgets error");
		close(fd[1]);
		if (waitpid(pid, NULL, 0) < 0)
			ERROR("waitpid error");
		exit(0);
	}
	else
	{
		close(fd[1]);
		if (fd[0] != STDIN_FILENO)
		{
			if (dup2(fd[0], STDIN_FILENO) != STDIN_FILENO)
				ERROR("dup2 error");
			close(fd[0]);
		}
		if ((pager = getenv("PAGER")) == NULL)
			pager =  DEF_PAGER;
		if ((argv0 = strrchr(pager, '/')) != NULL)
			argv0++;
		else
			argv0 = pager;
		if (execl(pager, argv0, (char *)0) < 0)
			ERROR("execl error");
	}
	exit(0);
}
