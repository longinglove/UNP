/*************************************************************************
	> File Name: kirk.c
	> Author: duqinglong
	> Mail: du_303412@163.com 
	> Created Time: 2016年03月24日 星期四 19时54分08秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<string.h>
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
		exit(1);
	}

	if ((msqid = msgget(key, 0644|IPC_CREAT)) == -1)
	{
		perror("msgget");
		exit(1);
	}

	printf("Enter lines of text, ^D to quit:\n");
	buf.mtype = 1;
	while (fgets(buf.mtext, sizeof(buf.mtext), stdin) != NULL)
	{
		int len = strlen(buf.mtext);
		if (buf.mtext[len-1] == '\n')
			buf.mtext[len-1] = 0;
		if (msgsnd(msqid, &buf, len+1, 0) == -1)
			perror("msgsnd");
	}
	if (msgctl(msqid, IPC_RMID, NULL) == -1)
	{
		perror("msgctl");
		exit(1);
	}
	exit(0);
}
