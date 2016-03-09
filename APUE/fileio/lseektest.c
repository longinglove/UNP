/*************************************************************************
    > File Name: lseektest.c
    > Author: duqinglong
    > Mail: du_303412@163.com 
    > Created Time: Tue 08 Mar 2016 03:09:51 PM CST
 ************************************************************************/

#include"../apue.h"

int main()
{
	if (lseek(STDIN_FILENO, 0, SEEK_CUR) == -1)
		printf("cannot seek\n");
	else
		printf("seek ok\n");
	return 0;
}

