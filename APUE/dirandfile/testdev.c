/*************************************************************************
	> File Name: testdev.c
	> Author: duqinglong
	> Mail: du_303412@163.com 
	> Created Time: 2016年03月10日 星期四 17时01分52秒
 ************************************************************************/

#include "../apue.h"
#include <sys/sysmacros.h>
#include <sys/types.h>
#ifdef SOLARIS
#include <sys/mkdev.h>
#endif

int main(int argc, char *argv[])
{
	int		i;
	struct stat	buf;
	for (i = 1; i < argc; i++)
	{
		printf("%s:", argv[i]);
		if (stat(argv[i], &buf) < 0)
		{
			printf("stat error\n");
			continue;
		}
		printf("dev = %d/%d", major(buf.st_dev), minor(buf.st_dev));
		if ( S_ISCHR(buf.st_mode) || S_ISBLK(buf.st_mode)) 
			printf(" (%s) rdev = %d/%d", (S_ISCHR(buf.st_mode)) ? "character" : "block", major(buf.st_rdev), minor(buf.st_rdev));
		printf("\n");
	}
	return 0;
}
