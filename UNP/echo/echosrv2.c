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

ssize_t writen(int fd, void* buf, size_t count);
ssize_t readn(int fd, void* buf, size_t count);

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
				while ((ret = readn(conn, recvbuf, BUFSIZE)) > 0)
				{
					printf("%s", recvbuf);
					if (writen(conn, recvbuf, ret) != ret)
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


ssize_t writen(int fd, void* buf, size_t count)
{
	char *bufp = (char *)buf;
	size_t nleft = count;
	ssize_t nwritten;

	while (nleft > 0)
	{
		if ((nwritten = write(fd, bufp, nleft)) < 0)
		{
			if (errno == EINTR)
				continue;
			return -1;
		}
		else if (nwritten == 0)
			continue;
		bufp += nwritten;
		nleft -= nwritten;
	}
	return count;
}

ssize_t readn(int fd, void* buf, size_t count)
{
	char *bufp = (char*)buf;
	size_t nleft = count;
	ssize_t nread;

	while (nleft > 0)
	{
		if ((nread = read(fd, bufp, nleft)) < 0)
		{
			if (errno == EINTR)
				continue;
			return -1;
		}
		else if (nread == 0)
			return count-nleft;
		bufp += nread;
		nleft -= nread;
	}
	return count;
}
