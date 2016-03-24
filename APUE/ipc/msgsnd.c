/*************************************************************************
	> File Name: msgsnd.c
	> Author: duqinglong
	> Mail: du_303412@163.com 
	> Created Time: 2016年03月24日 星期四 15时46分04秒
 ************************************************************************/

#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<stdlib.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#include<sys/types.h>
#include<sys/fcntl.h>

#define MSG_W 0200
#define BUF_SIZE 512

typedef struct msgbuf
{
	long mtype;
	char mdata[BUF_SIZE];
} mymsg_t;

int main(int argc, char **argv)
{
	int		mqid;
	size_t	msglen;
	long	msgtype;
	mymsg_t *ptr;

	if (argc != 3)
		puts("usage: send<pathname><type>");

	msgtype = atoi(argv[2]);
	mqid = msgget(ftok(argv[1], 0), MSG_W);
	ptr = calloc(sizeof(long)+msglen, sizeof(char));
	ptr->mtype = msgtype;
	snprintf(ptr->mdata, BUF_SIZE, "hello world");
	msglen = strlen(ptr->mdata);
	msgsnd(mqid, ptr, msglen, 0);

	exit(0);
}
