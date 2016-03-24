/*************************************************************************
	> File Name: example.c
	> Author: duqinglong
	> Mail: du_303412@163.com 
	> Created Time: 2016年03月22日 星期二 17时25分46秒
 ************************************************************************/

#include"../apue.h"
#include<errno.h>
#include<fcntl.h>

#define ERROR(m)	\
	do{perror(m);exit(EXIT_FAILURE);}while(0)

char buf[500000];

void set_fl(int fd, int flags)
{
	int	val;
	if ((val = fcntl(fd, F_GETFL, 0)) < 0)
		ERROR("fcntl F_GETFL error");
	val |= flags;
	if (fcntl(fd, F_SETFL, val) < 0)
		ERROR("fcntl F_SETFL error");
}

void clr_fl(int fd, int flags)
{
	int val;
	if ((val = fcntl(fd, F_GETFL, 0)) < 0)
		ERROR("fcntl F_GETFL error");
	val &= ~flags;
	if (fcntl(fd, F_SETFL, val) < 0)
		ERROR("fcntl F_SETFL error");
}

int main()
{
	int		ntowrite, nwrite;
	char	*ptr;

	ntowrite = read(STDIN_FILENO, buf, sizeof(buf));
	fprintf(stderr, "read %d bytes\n", ntowrite);

	set_fl(STDOUT_FILENO, O_NONBLOCK);

	ptr = buf;
	while (ntowrite > 0)
	{
		errno = 0;
		nwrite = write(STDOUT_FILENO, ptr, ntowrite);
		fprintf(stderr, "nwrite = %d, errno = %d\n", nwrite, errno);

		if (nwrite > 0)
		{
			ptr += nwrite;
			ntowrite -= nwrite;
		}
	}
	clr_fl(STDOUT_FILENO, O_NONBLOCK);
	exit(0);
}
