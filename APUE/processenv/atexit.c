/*************************************************************************
	> File Name: atexit.c
	> Author: duqinglong
	> Mail: du_303412@163.com 
	> Created Time: 2016年03月14日 星期一 10时07分23秒
 ************************************************************************/

#include "../apue.h"

#define ERROR(m)	\
	do {perror(m); exit(EXIT_FAILURE);} while (0)

static void my_exit1(void);
static void my_exit2(void);

int main()
{
	if (atexit(my_exit2) != 0)
		ERROR("atexit my_exit2 error");
	if (atexit(my_exit1) != 0)
		ERROR("atexit my_exit1 error");
	if (atexit(my_exit1) != 0)
		ERROR("atexit my_exit1 error");
	printf("main is done\n");
	return 0;
}

static void my_exit1(void)
{
	printf("my_exit1 handler\n");
}

static void my_exit2(void)
{
	printf("my_exit2 handler\n");
}
