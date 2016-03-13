/*************************************************************************
	> File Name: echosrv.c
	> Author: duqinglong
	> Mail: du_303412@163.com 
	> Created Time: 2016年03月11日 星期五 21时32分15秒
 ************************************************************************/

#include<stdio.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<unistd.h>
#include<stdlib.h>
#include<errno.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<string.h>

#define ERR_EXIT(m) \
	do \
	{	\
		perror(m);	\
		exit(EXIT_FAILURE);	\
	} while (0);

int main()
{
	char recvbuf[1024];
	int listenfd, conn, ret;
	struct sockaddr_in servaddr, peeraddr;
	socklen_t	peerlen = sizeof(peeraddr);
	if ((listenfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
		ERR_EXIT("socket error");
	memset(&servaddr, 0, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(5188);
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	if (bind(listenfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) < 0)
		ERR_EXIT("bind error");
	if (listen(listenfd, SOMAXCONN) < 0)
		ERR_EXIT("listen error");
	if ((conn = accept(listenfd, (struct sockaddr*)&peeraddr, &peerlen)) < 0)
		ERR_EXIT("accept error");
	printf("id = %s, port = %d\n", inet_ntoa(peeraddr.sin_addr), ntohs(peeraddr.sin_port));
	while (1)
	{
		memset(recvbuf, 0, sizeof(recvbuf));
		ret = read(conn, recvbuf, sizeof(recvbuf));
		fputs(recvbuf, stdout);
		write(conn, recvbuf, ret);
	}
	close(conn);
	close(listenfd);
	return 0;
}
