/*************************************************************************
	> File Name: rot_13.c
	> Author: duqinglong
	> Mail: du_303412@163.com 
	> Created Time: 2016年03月23日 星期三 14时53分37秒
 ************************************************************************/

#include "../apue.h"
#include <ctype.h>
#include <fcntl.h>

#define ERROR(m)	\
	do{perror(m);exit(EXIT_FAILURE);}while(0)

#define BSZ 4096

unsigned char buf[BSZ];

unsigned char translate(unsigned char c)
{
	if (isalpha(c))
	{
		if (c >= 'n')
			c -= 13;
		else if (c >= 'a')
			c += 13;
		else if (c >= 'N')
			c -= 13;
		else
			c += 13;
	}
	return c;
}

int main(int argc, char *argv[])
{
	int ifd, ofd, i, n, nw;
	if (argc != 3)
		ERROR("usage: rot13 infile outfile");
	if ((ifd = open(argv[1], O_RDONLY)) < 0)
		ERROR("open file error");
	if ((ofd = open(argv[2], O_RDWR|O_CREAT|O_TRUNC, FILE_MODE)) < 0)
		ERROR("cant create file");
	while ((n = read(ifd, buf, BSZ)) > 0)
	{
		for (i = 0; i < n; i++)
			buf[i] = translate(buf[i]);
		if ((nw = write(ofd, buf, n)) != n)
		{
			if (nw < 0)
				ERROR("write error");
			else
				ERROR("short write");
		}
	}
	fsync(ofd);
	exit(0);
}
