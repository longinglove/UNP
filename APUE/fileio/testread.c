/*************************************************************************
	> File Name: testread.c
	> Author: duqinglong
	> Mail: du_303412@163.com 
	> Created Time: 2016年03月13日 星期日 10时59分11秒
 ************************************************************************/

#include<stdio.h>

#define ERROR(m)	\
	do {perror(m); exit(EXIT_FAILURE);} while (0)
#define BUFSIZE 1024

int main()
{
	char buf[BUFSIZE];
	int n;
//	while ((n = read(0, buf, BUFSIZE)) > 0)
//		write(1, buf, n);

	return 0;
}

//getchar() version 1
int getchar(void)
{
	char c;
	return (read(0, &c, 1) == 1)?(unsigned char)c:EOF;
}

//getchar() version 2
int getchar(void)
{
	static char buf[BUFSIZE];
	static char *bufp = buf;
	static int n = 0;
	if (n == 0)
	{
		n = read(0, buf, sizeof(buf));
		bufp = buf;
	}
	return (--n >= 0)?(unsigned char)*bufp++:EOF;
}
