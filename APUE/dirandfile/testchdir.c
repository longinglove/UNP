/*************************************************************************
	> File Name: testchdir.c
	> Author: duqinglong
	> Mail: du_303412@163.com 
	> Created Time: 2016年03月10日 星期四 16时47分53秒
 ************************************************************************/

#include"../apue.h"

int main()
{
	if (chdir("/tmp") < 0)
		printf("chdir failed\n");
	printf("chdir to /tmp succeeded\n");
	return 0;
}

