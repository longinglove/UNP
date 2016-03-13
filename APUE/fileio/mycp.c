/*************************************************************************
	> File Name: mycp.c
	> Author: duqinglong
	> Mail: du_303412@163.com 
	> Created Time: 2016年03月13日 星期日 11时11分36秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<fcntl.h>

#define ERROR(m)	\
	do {perror(m); exit(EXIT_FAILURE);} while (0)
#define BUFSIZE 1024
#define PERMS 0666

int main(int argc, char *argv[])
{
	int f1, f2, n;
	char buf[BUFSIZE];

	if (argc != 3)
		ERROR("input error");
	if ((f1 = open(argv[1], O_RDONLY, 0)) == -1)
		ERROR("open f1 error");
	if ((f2 = creat(argv[2], PERMS)) == -1)
		ERROR("create f2 error");
	while ((n = read(f1, buf, BUFSIZE)) > 0)
		if (write(f2, buf, n) != n)
			ERROR("write error");
	return 0;
}
