/*************************************************************************
	> File Name: testgrp.c
	> Author: duqinglong
	> Mail: du_303412@163.com 
	> Created Time: 2016年03月11日 星期五 17时24分19秒
 ************************************************************************/

#include "../apue.h"
#include <grp.h>

#define handle_error(msg) \
	do { perror(msg); exit(EXIT_FAILURE); } while (0)

int main()
{
	struct group *test;
	gid_t	group_id;
	group_id = getgid();
	if ((test = getgrgid(group_id)) == NULL)
		handle_error("getgrgid error");
	printf("group name: %s\n", test->gr_name);
	printf("group id: %d\n", test->gr_gid);
	return 0;
}
