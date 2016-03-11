/*************************************************************************
	> File Name: echocl.c
	> Author: duqinglong
	> Mail: du_303412@163.com 
	> Created Time: 2016年03月11日 星期五 22时02分34秒
 ************************************************************************/

#include<stdio.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<stdlib.h>
#include<errno.h>
#include<string.h>
#include<netinet/in.h>
#include<arpa/inet.h>

#define ERR_EXIT(m)	\
	do	\
	{	\
		perror(m);	\
		exit(EXIT_FAILURE);	\
	} while (0);

int main()
{
	char sendbuf[1024] = {0}, recvbuf[1024] = {0};
	int sock;
	struct sockaddr_in servaddr;
	if ((sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
		printf("sock error");
	memset(&servaddr, 0, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(5188);
	servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	if (connect(sock, (struct sockaddr*)&servaddr, sizeof(servaddr)) < 0)
		ERR_EXIT("connect error");
	while (fgets(sendbuf, 1024, stdin) != NULL)
	{
		write(sock, sendbuf, strlen(sendbuf));
		read(sock, recvbuf, sizeof(recvbuf));
		fputs(recvbuf, stdout);
		memset(sendbuf, 0, sizeof(sendbuf));
		memset(recvbuf, 0, sizeof(recvbuf));
	}
	close(sock);
	return 0;
}
