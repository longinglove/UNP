/*************************************************************************
	> File Name: p2psrv.c
	> Author: duqinglong
	> Mail: du_303412@163.com 
	> Created Time: 2016年03月13日 星期日 16时12分49秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<errno.h>
#include<string.h>
#include<sys/types.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<signal.h>

#define BUFSIZE 1024
#define ERROR(m)	\
	do {perror(m); exit(EXIT_FAILURE);} while (0)

void handler(int sig);

int main()
{
	char rcvbuf[BUFSIZE];
	int sock, conn, on = 1, ret;
	struct sockaddr_in srvaddr, peeraddr;
	socklen_t peerlen = sizeof(peeraddr);
	pid_t pid;
	if ((sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
		ERROR("socket error");
	memset(&srvaddr, 0, sizeof(srvaddr));
	srvaddr.sin_family = AF_INET;
	srvaddr.sin_port = htons(4321);
	srvaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	if (setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on)) < 0)
		ERROR("setsockopt error");
	if (bind(sock, (struct sockaddr*)&srvaddr, sizeof(srvaddr)) < 0)
		ERROR("bind error");
	if (listen(sock, SOMAXCONN) < 0)
		ERROR("listen error");
	if ((conn = accept(sock, (struct sockaddr*)&peeraddr, &peerlen)) < 0)
		ERROR("accept error");
	printf("id = %s, port = %d\n", inet_ntoa(peeraddr.sin_addr), ntohs(peeraddr.sin_port));
	if ((pid = fork()) == -1)
		ERROR("fork error");
	if (pid == 0)
	{
		signal(SIGUSR1, handler);
		char sendbuf[BUFSIZE] = {0};
		while (fgets(sendbuf, BUFSIZE, stdin) != NULL)
		{
			write(conn, sendbuf, strlen(sendbuf));
			memset(sendbuf, 0, BUFSIZE);
		}
		printf("child close\n");
		exit(EXIT_SUCCESS);
	}
	else
	{
		while (1)
		{
			memset(rcvbuf, 0, BUFSIZE);
			if ((ret = read(conn, rcvbuf, BUFSIZE)) == -1)
				ERROR("read error");
			if (ret == 0)
			{
				printf("peer close\n");
				break;
			}
			printf("%s", rcvbuf);
		}
		printf("parent close\n");
		kill(pid, SIGUSR1);
		exit(EXIT_SUCCESS);
	}
	return 0;
}


void handler(int sig)
{
	printf("recv a sig = %d\n", sig);
	exit(EXIT_SUCCESS);
}
