/*************************************************************************
	> File Name: my_alarm.c
	> Author: duqinglong
	> Mail: du_303412@163.com 
	> Created Time: 2016年03月17日 星期四 10时39分26秒
 ************************************************************************/

#include "../apue.h"
#include<pwd.h>

#define ERROR(m)	\
	do {perror(m);exit(EXIT_FAILURE);} while (0)

static void my_alarm(int);

int main()
{
	struct passwd *ptr;
	signal(SIGALRM, my_alarm);
	alarm(1);
	for ( ; ; )
	{
		if ((ptr = getpwnam("silence")) == NULL)
			ERROR("getpwnam error");
		if (strcmp(ptr->pw_name, "silence") != 0)
			printf("retrun value corrupted!, pw_name = %s\n", ptr->pw_name);
	}
	exit(0);
}

static void my_alarm(int signo)
{
	struct passwd *rootptr;

	printf("in signal handler\n");
	if ((rootptr = getpwnam("root")) == NULL)
		ERROR("getpwnam(root) error");
	alarm(1);
}
