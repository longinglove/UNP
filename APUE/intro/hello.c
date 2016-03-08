/*************************************************************************
    > File Name: hello.c
    > Author: duqinglong
    > Mail: du_303412@163.com 
    > Created Time: Mon 07 Mar 2016 08:35:54 PM CST
 ************************************************************************/

#include"../apue.h"

int main()
{
	printf("hello world from process ID %ld\n", (long)getpid());
	printf("uid:%d, gid:%d\n", getuid(), getgid());
	return 0;
}

