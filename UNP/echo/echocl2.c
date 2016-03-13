/*************************************************************************
	> File Name: echocl2.c
	> Author: duqinglong
	> Mail: du_303412@163.com 
	> Created Time: 2016年03月13日 星期日 12时12分40秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<errno.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<arpa/inet.h>
#include<netinet/in.h>

#define ERROR(m)	\
	do {perror(m); exit(EXIT_FAILURE);} while (0)
#define BUFSIZE 1024

int main()
{
	struct sockaddr_in srvaddr;
	char recvbuf[BUFSIZE] = {0}, sendbuf[BUFSIZE] = {0};
	int sock, ret;
	if ((sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
		ERROR("socket error");
	srvaddr.sin_family = AF_INET;
	srvaddr.sin_port = htons(4321);
	srvaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	if (connect(sock, (struct sockaddr*)&srvaddr, sizeof(srvaddr)) < 0)
		ERROR("connect error");
	while (fgets(sendbuf, BUFSIZE, stdin) != NULL)
	{
		write(sock, sendbuf, BUFSIZE);
		read(sock, recvbuf, BUFSIZE);
		printf("%s", recvbuf);
		memset(recvbuf, 0, BUFSIZE);
		memset(sendbuf, 0, BUFSIZE);
	}
	return 0;
}
