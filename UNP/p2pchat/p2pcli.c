/*************************************************************************
	> File Name: p2pcli.c
	> Author: duqinglong
	> Mail: du_303412@163.com 
	> Created Time: 2016年03月13日 星期日 16时04分55秒
 ************************************************************************/

#include<signal.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<errno.h>

#define BUFSIZE 1024
#define ERROR(m)	\
	do {perror(m); exit(EXIT_FAILURE);} while (0)

void handler(int sig);

int main()
{
	char recvbuf[BUFSIZE] = {0}, sendbuf[BUFSIZE] = {0};
	int sock, ret;
	struct sockaddr_in srvaddr;
	pid_t pid;
	if ((sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
		ERROR("sock error");
	memset(&srvaddr, 0, sizeof(srvaddr));
	srvaddr.sin_family = AF_INET;
	srvaddr.sin_port = htons(4321);
	srvaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	if (connect(sock, (struct sockaddr*)&srvaddr, sizeof(srvaddr)) < 0)
		ERROR("connect error");
	if ((pid = fork()) < 0)
		ERROR("fork error");
	if (pid == 0)
	{
		while (1)
		{
			memset(recvbuf, 0, sizeof(recvbuf));
			if ((ret = read(sock, recvbuf, BUFSIZE)) < 0)
				ERROR("read error");
			else if (ret == 0)
			{
				printf("peer close\n");
				break;
			}
			else
				printf("%s", recvbuf);
		}
		close(sock);
		kill(getppid(), SIGUSR1);
	}
	else
	{
		signal(SIGUSR1, handler);
		while (fgets(sendbuf, BUFSIZE, stdin) != NULL)
		{
			write(sock, sendbuf, strlen(sendbuf));
			printf("%s", recvbuf);
			memset(sendbuf, 0, BUFSIZE);
		}
		printf("parent close\n");
		exit(EXIT_SUCCESS);
	}
	return 0;
}


void handler(int sig)
{
	printf("recv a sig = %d\n", sig);
	exit(EXIT_SUCCESS);
}
