/*************************************************************************
    > File Name: duptest.c
    > Author: duqinglong
    > Mail: du_303412@163.com 
    > Created Time: Tue 08 Mar 2016 04:17:39 PM CST
 ************************************************************************/

#include"../apue.h"
#include<fcntl.h>

int main()
{
	int fd;
	fd = open("/dev/fd/0", O_RDWR);
	printf("%d\n", fd);
	if ((fd = dup(1)) < 0)
		printf("error");
	printf("%d\n", fd);
	return 0;
}
