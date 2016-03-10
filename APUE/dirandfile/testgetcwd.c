/*************************************************************************
	> File Name: testgetcwd.c
	> Author: duqinglong
	> Mail: du_303412@163.com 
	> Created Time: 2016年03月10日 星期四 16时51分47秒
 ************************************************************************/

#include "../apue.h"

int main(int argc, char *argv[])
{
	char *ptr;
	if ((ptr = malloc(100)) == NULL)
		printf("malloc error");
	if (chdir("/usr") < 0)
		printf("chdir error");
	if (getcwd(ptr, 100) == NULL)
		printf("getcwd error");
	printf("cwd = %s\n", ptr);
	return 0;
}
