/*************************************************************************
	> File Name: testpause.c
	> Author: duqinglong
	> Mail: du_303412@163.com 
	> Created Time: 2016年03月17日 星期四 11时49分38秒
 ************************************************************************/

#include "../apue.h"

static void my_signal_alarm(unsigned int signo)
{
	printf("my_signal_alarm\n");
	return;
}

unsigned int my_sleep(unsigned int sleep_sec)
{
	if (signal(SIGALRM, my_signal_alarm) == SIG_ERR)
		return sleep_sec;
	alarm(sleep_sec);
	pause();
	printf("my_sleep\n");
	return (alarm(0));
}

int main()
{
	int re;
	re = my_sleep(3);
	printf("ret = %d\n", re);
	return 0;
}

