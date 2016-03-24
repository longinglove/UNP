/*************************************************************************
	> File Name: shm.c
	> Author: duqinglong
	> Mail: du_303412@163.com 
	> Created Time: 2016年03月24日 星期四 16时43分47秒
 ************************************************************************/

#include"../apue.h"
#include<sys/shm.h>

#define ARRAY_SIZE	40000
#define MALLOCK_SIZE 100000
#define SHM_SIZE	100000
#define SHM_MODE	0600

char array[ARRAY_SIZE];

int main()
{
	int		shmid;
	char	*ptr, *shmptr;

	printf("array[] from %p to %p \n", (void *)&array[0], (void *)&array[ARRAY_SIZE]);
	printf("stack around %p\n", (void *)&shmid);
	if ((ptr = malloc(MALLOCK_SIZE)) == NULL)
		fputs("malloc error", stdout);
	printf("malloc from %p to %p\n", (void *)ptr, (void *)ptr+MALLOCK_SIZE);

	if ((shmid = shmget(IPC_PRIVATE, SHM_SIZE, SHM_MODE)) < 0)
		fputs("shmget error", stdout);
	if ((shmptr = shmat(shmid, 0, 0)) == (void *)-1)
		fputs("shmat error", stdout);
	printf("shared memory attached from %p to %p\n", (void *)shmptr, (void *)shmptr+SHM_SIZE);
	if (shmctl(shmid, IPC_RMID, 0) < 0)
		fputs("shmctl error", stdout);
	exit(0);
}
