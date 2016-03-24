/*************************************************************************
	> File Name: msgget.c
	> Author: duqinglong
	> Mail: du_303412@163.com 
	> Created Time: 2016年03月24日 星期四 15时38分05秒
 ************************************************************************/

#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>

int main(int argc, char *argv[])
{
	int		c, flags;
	int		mqid;
	flags = IPC_CREAT;
	while ((c = getopt(argc, argv, "e")) != -1)
	{
		switch (c)
		{
			case 'e':
				flags |= IPC_EXCL;
				break;
		}
	}
	if (optind != argc - 1)
		puts("input: [-e][-m maxmsg][-z msgsize]<name>");

	mqid = msgget(ftok(argv[optind], 0), flags);
	exit(0);
}
