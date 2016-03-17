/*************************************************************************
	> File Name: sig.c
	> Author: duqinglong
	> Mail: du_303412@163.com 
	> Created Time: 2016年03月17日 星期四 10时50分20秒
 ************************************************************************/

#include<stdio.h>
#include<signal.h>

struct two_int
{
	int a;
	int b;
} data;

void signal_handler(int signo)
{
	printf("%d %d\n", data.a, data.b);
	alarm(1);
}

int main()
{
	static struct two_int zeros = {0, 0}, ones = {1, 1};
	signal(SIGALRM, signal_handler);
	data = zeros;
	alarm(1);
	while (1)
	{
		data = zeros;
		data = ones;
	}
	return 0;
}
