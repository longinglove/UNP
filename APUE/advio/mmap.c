/*************************************************************************
	> File Name: mmap.c
	> Author: duqinglong
	> Mail: du_303412@163.com 
	> Created Time: 2016年03月23日 星期三 16时14分35秒
 ************************************************************************/

#include "../apue.h"
#include <fcntl.h>
#include <sys/mman.h>

#define COPYINCR (1024*1024*1024)

#define ERROR(m)	\
	do{perror(m);exit(EXIT_FAILURE);}while(0)

int main(int argc, char *argv[])
{
	int			fdin, fdout;
	void		*src, *dst;
	size_t		copysz;
	struct stat	sbuf;
	off_t		fsz = 0;

	if (argc != 3)
		ERROR("usage: input infile and outfile");
	if ((fdin = open(argv[1], O_RDONLY)) < 0)
		ERROR("read error");
	if ((fdout = open(argv[2], O_RDWR|O_CREAT|O_TRUNC, FILE_MODE)) < 0)
		ERROR("create error");
	if (fstat(fdin, &sbuf) < 0)				//获取输入文件长度
		ERROR("fstat error");				
	if (ftruncate(fdout, sbuf.st_size) < 0)			//设置输出文件长度
		ERROR("ftruncate error");

	while (fsz < sbuf.st_size)
	{
		if ((sbuf.st_size - fsz) > COPYINCR)
			copysz = COPYINCR;
		else
			copysz = sbuf.st_size - fsz;
		
		//两个文件映射到内存的地址
		if ((src = mmap(0, copysz, PROT_READ, MAP_SHARED, fdin, fsz)) == MAP_FAILED)
			ERROR("mmap error for input");
		if ((dst = mmap(0, copysz, PROT_READ|PROT_WRITE, MAP_SHARED, fdout, fsz)) == MAP_FAILED)
			ERROR("mmap error for output");
		memcpy(dst, src, copysz);
		munmap(src, copysz);
		munmap(dst, copysz);
		fsz += copysz;
	}
	exit(0);
}
