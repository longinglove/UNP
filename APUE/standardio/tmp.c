/*************************************************************************
	> File Name: tmp.c
	> Author: duqinglong
	> Mail: du_303412@163.com 
	> Created Time: 2016年03月11日 星期五 11时32分50秒
 ************************************************************************/

#include"../apue.h"

int main()
{
	char name[L_tmpnam], line[MAXLINE];
	FILE *fp;

	printf("%s\n", tmpnam(NULL));
	tmpnam(name);
	printf("%s\n", name);
	
	if ((fp = tmpfile()) == NULL)
		printf("tmpfile error");
	fputs("one line of output\n", fp);
	rewind(fp);
	if (fgets(line, sizeof(line), fp) == NULL)
		printf("fgets error");
	fputs(line, stdout);
	return 0;
}
