/*************************************************************************
	> File Name: mkstemp.c
	> Author: duqinglong
	> Mail: du_303412@163.com 
	> Created Time: 2016年03月11日 星期五 11时50分12秒
 ************************************************************************/

#include "../apue.h"
#include <errno.h>

void make_temp(char *template);

int main()
{
	char	good_template[] = "/tmp/dirXXXXXX";
	char	*bad_template = "/tmp/dirXXXXXX";

	printf("trying to create first temp file...\n");
	make_temp(good_template);
	printf("trying to create second temp file...\n");
	make_temp(bad_template);
	return 0;
}

void make_temp(char *template)
{
	int			fd;
	struct stat	sbuf;
	if ((fd = mkstemp(template)) < 0)
		printf("cannt create temp file");
	printf("temp name = %s\n", template);
	close(fd);
	if (stat(template, &sbuf) < 0)
	{
		if (errno == ENOENT)
			printf("file doesnt exit\n");
		else
			printf("stat failed\n");
	}
	else
	{
		printf("file exists\n");
		unlink(template);
	}
}
