/*************************************************************************
	> File Name: stream.c
	> Author: duqinglong
	> Mail: du_303412@163.com 
	> Created Time: 2016年03月11日 星期五 15时09分04秒
 ************************************************************************/

#include "../apue.h"

#define BSZ 48

#define handle_error(msg) \
	           do { perror(msg); exit(EXIT_FAILURE); } while (0)


void is_unbuffered(FILE *fp)
{
	if (fp->_flags & _IO_UNBUFFERED)
		printf("unbufferd\n");
	else if (fp->_flags & _IO_LINE_BUF)
		printf("line buffered\n");
	else 
		printf("buffer size %d\n", fp->_IO_buf_end - fp->_IO_buf_base);
}

int main()
{
	FILE *fp;
	char buf[BSZ];

	memset(buf, 'a', BSZ-2);
	buf[BSZ-2] = '\0';
	buf[BSZ-1] = 'X';

	if ((fp = fmemopen(buf, BSZ, "w+")) == NULL)
		handle_error("fmemopen error\n");

	is_unbuffered(fp);

	printf("initial buffer contents: %s\n", buf);
	fprintf(fp, "hello, world\n");
	printf("before flush: %s\n", buf);
	fflush(fp);
	printf("after flush: %s\n", buf);
	printf("len of string in buf = %ld\n", (long)strlen(buf));

	memset(buf, 'b', BSZ-2);
	buf[BSZ-2] = '\0';
	buf[BSZ-1] = 'X';
	fprintf(fp, "hello, world\n");
	fseek(fp, 0, SEEK_SET);
	printf("after seek: %s\n", buf);
	printf("len of string in buf = %ld\n", (long)strlen(buf));

	memset(buf, 'c', BSZ-2);
	buf[BSZ-2] = '\0';
	buf[BSZ-1] = 'X';
	fprintf(fp, "hello, world");
	fclose(fp);
	printf("after close: %s\n", buf);
	printf("len of string in buf = %ld\n", (long)strlen(buf));
	return 0;
}
