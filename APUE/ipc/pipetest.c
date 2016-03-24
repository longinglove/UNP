/*************************************************************************
	> File Name: pipetest.c
	> Author: duqinglong
	> Mail: du_303412@163.com 
	> Created Time: 2016年03月24日 星期四 10时16分25秒
 ************************************************************************/

#include"../apue.h"

#define ERROR(m)	\
	do{perror(m);exit(EXIT_FAILURE);}while(0)

int main()
{
	int		n;
	int		fd[2];
	pid_t	pid;
	char	line[MAXLINE];
	
	//管道只能在具有公共祖先的两个进程之间使用，通常管道由一个进程创建，在进程调用fork之后，这个管道就能在父进程和子进程之间使用了
	if (pipe(fd) < 0)
		ERROR("pipe error");
	if ((pid = fork()) < 0)
		ERROR("fork error");
	else if (pid > 0)
	{
		close(fd[0]);
		write(fd[1], "hello world\n", 12);
	}
	else
	{
		close(fd[1]);
		n = read(fd[0], line, MAXLINE);
		write(STDIN_FILENO, line, n);
	}
	exit(0);
}
