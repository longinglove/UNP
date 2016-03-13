/*************************************************************************
    > File Name: lsimpl.c
    > Author: duqinglong
    > Mail: du_303412@163.com 
    > Created Time: Fri 04 Mar 2016 10:26:44 PM CST
 ************************************************************************/

#include"../apue.h"
#include<dirent.h>

#define ERROR(m)	\
	do {perror(m); exit(EXIT_FAILURE);} while (0)

int main(int argc, char* argv[])
{
	DIR		*dp;
	struct dirent	*dirp;

	if (argc != 2)
		ERROR("input error");
	if ((dp = opendir(argv[1])) == NULL)
		ERROR("opendir error");
	while ((dirp = readdir(dp)) != NULL)
		printf("%s\n", dirp->d_name);
	closedir(dp);
	return 0;
}

