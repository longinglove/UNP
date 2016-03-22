/*************************************************************************
	> File Name: daemon.h
	> Author: duqinglong
	> Mail: du_303412@163.com 
	> Created Time: 2016年03月22日 星期二 16时01分39秒
 ************************************************************************/

#ifndef _DAEMON_H_
#define _DAEMON_H_

#include "../apue.h"
#include <syslog.h>
#include <fcntl.h>
#include <sys/resource.h>

void daemonize(const char *cmd);

#endif
