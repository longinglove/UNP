/*************************************************************************
	> File Name: aioexample.c
	> Author: duqinglong
	> Mail: du_303412@163.com 
	> Created Time: 2016年03月23日 星期三 15时43分02秒
 ************************************************************************/

#include <aio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#define BUFSIZE 256

int main()
{
	struct aiocb cbp;
	int			 fd, ret;
	int			 i = 0;

	if ((fd = open("test", O_RDONLY)) < 0)
	{
		perror("open error\n");
		exit(EXIT_FAILURE);
	}

	bzero(&cbp, sizeof(cbp));
	cbp.aio_buf = (volatile void*)malloc(BUFSIZE+1);
	cbp.aio_nbytes = BUFSIZE;
	cbp.aio_offset = 0;
	cbp.aio_fildes = fd;
	ret = aio_read(&cbp);
	if (ret < 0)
	{
		perror("aio_read error\n");
		exit(EXIT_FAILURE);
	}
	for (i = 1; aio_error(&cbp) == EINPROGRESS; i++)
		printf("No.%3d\n", i);
	ret = aio_return(&cbp);
	printf("return %d\n", ret);
	
	sleep(1);
	printf("%s\n", (char *)cbp.aio_buf);
	close(fd);
	exit(0);
}
