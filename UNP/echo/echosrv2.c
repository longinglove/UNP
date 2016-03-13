/*************************************************************************
	> File Name: echosrv2.c
	> Author: duqinglong
	> Mail: du_303412@163.com 
	> Created Time: 2016年03月13日 星期日 11时44分59秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<errno.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>

#define ERROR(m)	\
	do {perror(m); exit(EXIT_FAILURE);} while (0)
#define BUFSIZE 1024

int main()
{
	char recvbuf[BUFSIZE];
	struct sockaddr_in servaddr, peeraddr;
	int sock, conn, ret, on;
	pid_t pid;
	socklen_t peerlen = sizeof(peeraddr);
	if ((sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
		ERROR("sock error");
	memset(&servaddr, 0, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(4321);
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	if (setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on)) < 0)
		ERROR("setsockopt error");
	if (bind(sock, (struct sockaddr*)&servaddr, sizeof(servaddr)) < 0)
		ERROR("bind error");
	if (listen(sock, SOMAXCONN) < 0)
		ERROR("listen error");
	while (1)
	{
		if ((conn = accept(sock, (struct sockaddr*)&peeraddr, &peerlen)) < 0)
			ERROR("accept error");
		printf("ip = %s, port = %d\n", inet_ntoa(peeraddr.sin_addr), ntohs(peeraddr.sin_port));
		if ((pid = fork()) == -1)
			ERROR("fork");
		if (pid == 0)
		{
			close(sock);
			while (1)
			{
				memset(recvbuf, 0, BUFSIZE);
				while ((ret = read(conn, recvbuf, BUFSIZE)) > 0)
				{
					printf("%s", recvbuf);
					if (write(conn, recvbuf, ret) != ret)
						ERROR("write error");
				}
				if (ret == 0)
				{
					printf("client_close\n");
					exit(EXIT_SUCCESS);
				}
				else if (ret == -1)
					ERROR("read error");
			}
		}
		else
			close(conn);
	}
	close(sock);
	close(conn);
	return 0;
}
