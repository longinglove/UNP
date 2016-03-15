/*************************************************************************
	> File Name: login.c
	> Author: duqinglong
	> Mail: du_303412@163.com 
	> Created Time: 2016年03月15日 星期二 18时04分52秒
 ************************************************************************/

#include "../apue.h"
#include <pwd.h>

int main()
{
	struct passwd *out;
	out = getpwuid(getuid());
	printf("getlogin:%s\n", getlogin());
	printf("getpwuid:%s\n", out->pw_name);
	exit(0);
}
