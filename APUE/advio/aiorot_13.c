/*************************************************************************
	> File Name: aiorot_13.c
	> Author: duqinglong
	> Mail: du_303412@163.com 
	> Created Time: 2016年03月23日 星期三 15时08分13秒
 ************************************************************************/

#include "../apue.h"
#include <ctype.h>
#include <fcntl.h>
#include <aio.h>
#include <errno.h>

#define BSZ 4096
#define NBUF 8

#define ERROR(m)	\
	do{perror(m);exit(EXIT_FAILURE);}while(0)

enum rwop {
	UNUSED = 0,
	READ_PENDING = 1,
	WRITE_PENDING = 2
};

struct buf {
	enum rwop	op;
	int			last;
	struct aiocb	aiocb;
	unsigned char	data[BSZ];
};

struct buf bufs[NBUF];

unsigned char translate(unsigned char c)
{
	if (isalpha(c))
	{
		if (c >= 'n')
			c -= 13;
		else if (c >= 'a')
			c += 13;
		else if (c >= 'N')
			c -= 13;
		else
			c += 13;
	}
	return c;
}

int main(int argc, char *argv[])
{
	int					ifd, ofd, i, j, n, err, numop;
	struct stat			sbuf;
	const struct aiocb	*aiolist[NBUF];
	off_t				off = 0;

	if (argc != 3)
		ERROR("usage: rot13 infile outfile");
	if ((ifd = open(argv[1], O_RDONLY)) < 0)
		ERROR("open error");
	if ((ofd = open(argv[2], O_RDWR|O_CREAT|O_TRUNC, FILE_MODE)) < 0)
		ERROR("create file error");
	if (fstat(ifd, &sbuf) < 0)
		ERROR("fstat failed");

	numop = 0;
	for ( ; ; )
	{
		for (i = 0; i < NBUF; i++)
		{
			switch (bufs[i].op) 
			{
				case UNUSED:
					if (off < sbuf.st_size)
					{
						bufs[i].op = READ_PENDING;
						bufs[i].aiocb.aio_fildes = ifd;
						bufs[i].aiocb.aio_offset = off;
						off += BSZ;
						if (off >= sbuf.st_size)
							bufs[i].last = 1;
						bufs[i].aiocb.aio_nbytes = BSZ;
						if (aio_read(&bufs[i].aiocb) < 0)
							ERROR("aio_read error");
						aiolist[i] = &bufs[i].aiocb;
						numop++;
					}
					break;

				case READ_PENDING:
					if ((err = aio_error(&bufs[i].aiocb)) == EINPROGRESS)
						continue;
					if (err != 0)
					{
						if (err == -1)
							ERROR("aio_error error");
						else
							ERROR("read failed");
					}
					if ((n = aio_return(&bufs[i].aiocb)) < 0)
						ERROR("aio_return error");
					if (n != BSZ && !bufs[i].last)
						ERROR("short read");
					for (j = 0; j < n; j++)
						bufs[i].data[j] = translate(bufs[i].data[j]);
					bufs[i].op = WRITE_PENDING;
					bufs[i].aiocb.aio_fildes = ofd;
					bufs[i].aiocb.aio_nbytes = n;
					if (aio_write(&bufs[i].aiocb) < 0)
						ERROR("aio_write error");
					break;

				case WRITE_PENDING:
					if ((err = aio_error(&bufs[i].aiocb)) < EINPROGRESS)
						continue;
					if (err != 0)
					{
						if (err == -1)
							ERROR("aio_error failed");
						else
							ERROR("write failed");
					}
					if ((n = aio_return(&bufs[i].aiocb)) < 0)
						ERROR("aio_return failed");
					if (n != bufs[i].aiocb.aio_nbytes)
						ERROR("short write");
					aiolist[i] = NULL;
					bufs[i].op = UNUSED;
					numop--;
					break;
			}
		}
		if (numop == 0)
		{
			if (off >= sbuf.st_size)
				break;
		}
		else
		{
			if (aio_suspend(aiolist, NBUF, NULL) < 0)
				ERROR("aio_suspend failed");
		}
	}
	bufs[0].aiocb.aio_fildes = ofd;
	if (aio_fsync(O_SYNC, &bufs[0].aiocb) < 0)
		ERROR("aio_fsync failed");
	exit(0);
}
