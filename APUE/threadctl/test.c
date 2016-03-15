/*************************************************************************
	> File Name: test.c
	> Author: duqinglong
	> Mail: du_303412@163.com 
	> Created Time: 2016年03月15日 星期二 11时46分35秒
 ************************************************************************/

#include "../apue.h"

int main()
{
	printf("uid = %ld, gid = %ld, euid = %ld, egid = %ld\n", (long)getuid(), (long)getgid(), (long)geteuid(), (long)getegid());
	exit(0);
}
