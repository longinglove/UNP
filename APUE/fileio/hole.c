/*************************************************************************
    > File Name: hole.c
    > Author: duqinglong
    > Mail: du_303412@163.com 
    > Created Time: Tue 08 Mar 2016 03:23:10 PM CST
 ************************************************************************/

#include"../apue.h"

char buf1[] = "abcdefghij";
char buf2[] = "ABCDEFGHIJ";

int main()
{
	int fd;

	if ((fd = creat("file.hole", FILE_MODE)) < 0)
		printf("Creat error");

	if (write(fd, buf1, 10) != 10)
		printf("buf1 write error");

	if (lseek(fd, 16384, SEEK_SET) == -1)
		printf("lseek error");
	if (write(fd, buf2, 10) != 10)
		printf("buf2 write error");
	return 0;
}

