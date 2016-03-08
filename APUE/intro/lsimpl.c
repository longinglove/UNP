/*************************************************************************
    > File Name: lsimpl.c
    > Author: duqinglong
    > Mail: du_303412@163.com 
    > Created Time: Fri 04 Mar 2016 10:26:44 PM CST
 ************************************************************************/

#include"../apue.h"
#include<dirent.h>

int main(int argc, char* argv[])
{
	DIR		*dp;
	struct dirent	*dirp;

	if (argc != 2)
	{
		printf("usage: ls directory_name\n");
		exit(0);
	}
	if ((dp = opendir(argv[1])) == NULL)
		printf("cant open %s", argv[1]);
	while ((dirp = readdir(dp)) != NULL)
		printf("%s\n", dirp->d_name);
	closedir(dp);
	return 0;
}

