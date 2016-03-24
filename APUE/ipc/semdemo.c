/*************************************************************************
	> File Name: semdemo.c
	> Author: duqinglong
	> Mail: du_303412@163.com 
	> Created Time: 2016年03月24日 星期四 20时27分49秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<errno.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/sem.h>

#define MAX_RETRIES		1
#define ERROR(m)	\
	do{perror(m);exit(EXIT_FAILURE);}while(0)

union semun {
	int		val;
	struct semid_ds	*buf;
	ushort	*array;
};

int initsem(key_t key, int nsems)
{
	int		i;
	union semun	arg;
	struct semid_ds	buf;
	struct sembuf	sb;
	int		semid;

	semid = semget(key, nsems, IPC_CREAT|IPC_EXCL|0666);

	if (semid >= 0)
	{
		sb.sem_op = 1;
		sb.sem_flg = 0;
		arg.val = 1;

		printf("press return\n");
		getchar();
		for (sb.sem_num = 0; sb.sem_num < nsems; sb.sem_num++)
		{
			if (semop(semid, &sb, 1) == -1)
			{
				int e = errno;
				semctl(semid, 0, IPC_RMID);
				errno = e;
				return -1;
			}
		}
	}
	else if (errno == EEXIST)
	{
		int ready = 0;
		semid = semget(key, nsems, 0);
		if (semid < 0)
			return semid;
		arg.buf = &buf;
		for (i = 0; i < MAX_RETRIES && !ready; i++)
		{
			semctl(semid, nsems-1, IPC_STAT, arg);
			if (arg.buf->sem_otime != 0)
				ready = 1;
			else
				sleep(1);
		}
		if (!ready)
		{
			errno = ETIME;
			return -1;
		}
	}
	else
		return semid;
	return semid;
}

int main()
{
	key_t	key;
	int		semid;
	struct sembuf	sb;
	sb.sem_num = 0;
	sb.sem_op = -1;
	sb.sem_flg = SEM_UNDO;

	if ((key = ftok("semdemo.c", 'J')) == -1)
		ERROR("ftok");
	if ((semid = initsem(key, 1)) == -1)
		ERROR("semid");

	printf("Press return to lock: ");
	getchar();
	printf("Try to lock...\n");

	if (semop(semid, &sb, 1) == -1)
		ERROR("semop");
	printf("Locked.\n");
	printf("Press return to unlock: ");

	sb.sem_op = 1;
	if (semop(semid, &sb, 1) == -1)
		ERROR("semoop");
	printf("Unlocked\n");
	exit(0);
}
