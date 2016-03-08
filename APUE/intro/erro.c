/*************************************************************************
    > File Name: erro.c
    > Author: duqinglong
    > Mail: du_303412@163.com 
    > Created Time: Mon 07 Mar 2016 10:04:41 PM CST
 ************************************************************************/

#include"../apue.h"
#include<errno.h>

int main(int argc, char *argv[])
{
	fprintf(stderr, "EACCES:%s\n", strerror(EACCES));
	errno = ENOENT;
	perror(argv[0]);
	return 0;
}

