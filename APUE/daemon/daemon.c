/*************************************************************************
	> File Name: daemon.c
	> Author: duqinglong
	> Mail: du_303412@163.com 
	> Created Time: 2016年03月22日 星期二 16时10分05秒
 ************************************************************************/

#include "daemon.h"

#define ERROR(m)	\
	do{perror(m);exit(EXIT_FAILURE);}while(0)

void daemonize(const char *cmd)
{
	int					i, fd0, fd1, fd2;
	pid_t				pid;
	struct rlimit		rl;
	struct sigaction	sa;

	umask(0);

	if (getrlimit(RLIMIT_NOFILE, &rl) < 0)
		ERROR("cant get file limit");
	if ((pid = fork()) < 0)
		ERROR("fork error");
	else if (pid != 0)
		exit(0);
	setsid();

	sa.sa_handler = SIG_IGN;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	if (sigaction(SIGHUP, &sa, NULL) < 0)
		ERROR("sigaction error");
	if ((pid = fork()) < 0)
		ERROR("fork error");
	else if (pid != 0)
		exit(0);

	if (chdir("/") < 0)
		ERROR("change directory error");
	if (rl.rlim_max == RLIM_INFINITY)
		rl.rlim_max = 1024;
	for (i = 0; i < rl.rlim_max; i++)
		close(i);

	fd0 = open("/dev/null", O_RDWR);
	fd1 = dup(0);
	fd2 = dup(0);

	openlog(cmd, LOG_CONS, LOG_DAEMON);
	if (fd0 != 0 || fd1 != 1 || fd2 != 2)
	{
		syslog(LOG_ERR, "unexpected file descriptors %d %d %d", fd0, fd1, fd2);
		exit(1);
	}
}

