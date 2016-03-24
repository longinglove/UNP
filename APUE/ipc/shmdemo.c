/*************************************************************************
	> File Name: shmdemo.c
	> Author: duqinglong
	> Mail: du_303412@163.com 
	> Created Time: 2016年03月24日 星期四 21时15分17秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/shm.h>

#define SHM_SIZE 1024

int main(int argc, char *argv[])
{
	key_t	key;
	int		shmid;
	char	*data;
	int		mode;

	if (argc > 2)
	{
		fprintf(stderr, "usage: shmdemo [data_to_write]\n");
		exit(EXIT_FAILURE);
	}

	if ((key = ftok("shmdemo.c", 'R')) < 0)
	{
		perror("ftok");
		exit(EXIT_FAILURE);
	}

	if ((shmid = shmget(key, SHM_SIZE, 0644|IPC_CREAT)) == -1)
	{
		perror("shmget");
		exit(EXIT_FAILURE);
	}
	data = shmat(shmid, (void *)0, 0);
	if (data == (char *)-1)
	{
		perror("shmat");
		exit(EXIT_FAILURE);
	}
	if (argc == 2)
	{
		printf("writing to segment: \"%s\"\n", argv[1]);
		strncpy(data, argv[1], SHM_SIZE);
	}
	else
		printf("segment contains: \"%s\"\n", data);

	if (shmdt(data) == -1)
	{
		perror("shmdt");
		exit(EXIT_FAILURE);
	}
	exit(0);
}
