/*************************************************************************
	> File Name: spock.c
	> Author: duqinglong
	> Mail: du_303412@163.com 
	> Created Time: 2016年03月24日 星期四 19时58分52秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/msg.h>

struct my_msgbuf {
	long mtype;
	char mtext[200];
};

int main()
{
	struct my_msgbuf	buf;
	int					msqid;
	key_t				key;

	if ((key = ftok("kirk.c", 'B')) == -1)
	{
		perror("ftok");
		exit(EXIT_FAILURE);
	}
	if ((msqid = msgget(key, 0644)) == -1)
	{
		perror("msgget");
		exit(EXIT_FAILURE);
	}
	printf("spock: ready to receive messages, captain.\n");
	for ( ; ; )
	{
		if (msgrcv(msqid, &buf, sizeof(buf.mtext), 0, 0) == -1)
		{
			perror("msgrcv");
			exit(EXIT_FAILURE);
		}
		printf("spock:\"%s\"\n", buf.mtext);
	}
	exit(0);
}
