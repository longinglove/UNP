/*************************************************************************
	> File Name: poll.c
	> Author: duqinglong
	> Mail: du_303412@163.com 
	> Created Time: 2016年03月23日 星期三 17时31分04秒
 ************************************************************************/

#include<stdio.h>
#include<poll.h>
#include<unistd.h>
#include<stdlib.h>

#define TIMEOUT 5

int main()
{
	struct pollfd fds[2];
	int ret;

	fds[0].fd = STDIN_FILENO;
	fds[0].events = POLLIN;
	fds[1].fd = STDOUT_FILENO;
	fds[1].events = POLLOUT;

	ret = poll(fds, 2, TIMEOUT*1000);
	if (ret == -1)
	{
		perror("poll error");
		exit(1);
	}
	if (!ret)
	{
		printf("%d seconds elapsed.\n", TIMEOUT);
		return 0;
	}
	if (fds[0].revents & POLLIN)
		printf("stdin is readable\n");
	if (fds[1].revents & POLLOUT)
		printf("stdout is writable\n");
	exit(0);
}
