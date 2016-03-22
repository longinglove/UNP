/*************************************************************************
	> File Name: testdaemon.c
	> Author: duqinglong
	> Mail: du_303412@163.com 
	> Created Time: 2016年03月22日 星期二 16时18分08秒
 ************************************************************************/

#include "daemon.h"

int main(int argc, char *argv[])
{
	daemonize(argv[0]);
	pause();
	exit(0);
}
