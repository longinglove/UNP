/*************************************************************************
	> File Name: select.c
	> Author: duqinglong
	> Mail: du_303412@163.com 
	> Created Time: 2016年03月23日 星期三 17时12分48秒
 ************************************************************************/

#include<stdio.h>
#include<sys/time.h>
#include<sys/types.h>
#include<unistd.h>
#include<stdlib.h>

#define TIMEOUT 5
#define BUF_LEN 1024

int main()
{
	struct timeval	tv;
	fd_set			readfds;
	int				ret;

	FD_ZERO(&readfds);
	FD_SET(STDIN_FILENO, &readfds);
	tv.tv_sec = TIMEOUT;
	tv.tv_usec = 0;

	ret = select(STDIN_FILENO+1, &readfds, NULL, NULL, &tv);
	if (ret == -1)
	{
		perror("select error");
		exit(1);
	}
	else if (!ret)
	{
		printf("%d seconds elapsed.\n", TIMEOUT);
		return 0;
	}
	if (FD_ISSET(STDIN_FILENO, &readfds))
	{
		char buf[BUF_LEN+1];
		int len;
		len = read(STDIN_FILENO, buf, BUF_LEN);
		if (len == -1)
		{
			perror("read error");
			exit(1);
		}
		if (len)
		{
			buf[len] = '\0';
			printf("read:%s\n", buf);
		}
		return 0;
	}
	fprintf(stderr, "This should not happen!\n");
}
