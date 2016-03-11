/*************************************************************************
	> File Name: impl.c
	> Author: duqinglong
	> Mail: du_303412@163.com 
	> Created Time: 2016年03月11日 星期五 10时56分27秒
 ************************************************************************/

#include"../apue.h"

void pr_stdio(const char *, FILE *);
int	 is_unbuffered(FILE *);
int  is_linebuffered(FILE *);
int  buffer_size(FILE *);

int main()
{
	FILE *fp;
	fputs("enter any character\n", stdout);
	if (getchar() == EOF)
		printf("getchar error");
	fputs("one line to standard error\n", stderr);

	pr_stdio("stdin", stdin);
	pr_stdio("stdout", stdout);
	pr_stdio("stderr", stderr);

	if ((fp = fopen("/etc/passwd", "r")) == NULL)
		printf("open error");
	if (getc(fp) == EOF)
		printf("getc error");
	pr_stdio("/etc/passwd", fp);
	return 0;
}

void pr_stdio(const char *name, FILE *fp)
{
	printf("stream = %s, ", name);
	if (is_unbuffered(fp))
		printf("unbuffered");
	else if (is_linebuffered(fp))
		printf("line buffered");
	else
		printf("fully buffered");
	printf(", buffer size = %d\n", buffer_size(fp));
}

#if defined(_IO_UNBUFFERED)

int is_unbuffered(FILE *fp)
{
	return (fp->_flags & _IO_UNBUFFERED);
}

int is_linebuffered(FILE *fp)
{
	return (fp->_flags & _IO_LINE_BUF);
}

int buffer_size(FILE *fp)
{
	return (fp->_IO_buf_end - fp->_IO_buf_base);
}

#elif defined(__SNBF)

int is_unbuffered(FILE *fp)
{
	return (fp->_flags & __SNBF);
}

int is_linebuffferd(FILE *fp)
{
	return (fp->_fags & __SLBF);
}

int buffer_size(FILE *fp)
{
	return (fp->_bf._size);
}

#elif defined(_IONBF)

#ifdef _LP64
#define _flag __pad[4]
#define _ptr __pad[1]
#define _base __pad[2]
#endif

int is_unbuffered(FILE *fp)
{
	return (fp->_flag & _IONBF);
}

int is_linebuffered(FILE *fp)
{
	return (fp->_flag & _IOLBF);
}

int buffer_size(FILE *fp)
{
#ifdef _LP64
	return (fp->_base - fp->_ptr);
#else
	return (BUFFSIZ);
#endif
}

#else

#error unknown stdio implementation!

#endif