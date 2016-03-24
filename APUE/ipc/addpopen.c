/*************************************************************************
	> File Name: addpopen.c
	> Author: duqinglong
	> Mail: du_303412@163.com 
	> Created Time: 2016年03月24日 星期四 11时27分51秒
 ************************************************************************/

#include"../apue.h"

#define ERROR(m)	\
	do{perror(m);exit(EXIT_FAILURE);}while(0)

static void sig_pipe(int);

int main()
{
	int		n, fd1[2], fd2[2];
	pid_t	pid;
	char	line[MAXLINE];

	if (signal(SIGPIPE, sig_pipe) == SIG_ERR)
		ERROR("signal error");
	if (pipe(fd1) < 0 || pipe(fd2) < 0)
		ERROR("pipe error");

	if ((pid = fork()) < 0)
		ERROR("fork error");
	else if (pid > 0)
	{
		close(fd1[0]);
		close(fd2[1]);

		while (fgets(line, MAXLINE, stdin) != NULL)
		{
			n = strlen(line);
			if (write(fd1[1], line, n) != n)
				ERROR("write error");
			if ((n = read(fd2[0], line, MAXLINE)) < 0)
				ERROR("read error");
			if (n == 0)
			{
				ERROR("child close pipe");
				break;
			}
			line[n] = 0;
			if (fputs(line, stdout) == EOF)
				ERROR("fputs error");
		}
		if (ferror(stdin))
			ERROR("fgets error on stdin");
		exit(0);
	}
	else
	{
		close(fd1[1]);
		close(fd2[0]);

		if (fd1[0] != STDIN_FILENO)
		{
			if (dup2(fd1[0], STDIN_FILENO) != STDIN_FILENO)
				ERROR("dup2 error");
			close(fd1[0]);
		}
		if (fd2[1] != STDOUT_FILENO)
		{
			if (dup2(fd2[1], STDOUT_FILENO) != STDOUT_FILENO)
				ERROR("dup2 error");
			close(fd2[1]);
		}
		if (execl("./add2", "add2", (char *)0) < 0)
			ERROR("execl error");
	}
	exit(0);
}

static void sig_pipe(int signo)
{
	printf("SIGPIPE caught\n");
	exit(1);
}
