#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main()
{
	int fd =0, ret=0, rel=0, wrt=0;
	char buff[80]="";
	char wrtbuff[80]="WRITEBUFFER";

	fd = open("/dev/SAMPLE_DEVIC",O_RDONLY);
	printf("Fd :%d\n",fd);
	
	ret = read(fd,buff,10);
	buff[ret] = '\0';
	printf("Buffer: %s ; Length: %d bytes\n",buff,ret);
	
	wrt = write(fd,wrtbuff,10);

	close(fd);
	return 0;

}

