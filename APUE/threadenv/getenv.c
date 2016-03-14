/*************************************************************************
	> File Name: getenv.c
	> Author: duqinglong
	> Mail: du_303412@163.com 
	> Created Time: 2016年03月14日 星期一 10时52分04秒
 ************************************************************************/

#include "../apue.h"

int main()
{
	char *a = "HOME";
	printf("enviroment:%s\n", getenv(a));
	return 0;
}
