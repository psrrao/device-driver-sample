/* test_driver.c
*/
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <errno.h>

int main()
{
     int fd, i;
     int ret;
     char my_buf[4000] = { 0 };
            
     /* fill my buffer with *s */
     for(i=0; i<4000; i++) my_buf[i] = '*';

     /* open the device for read/write/lseek */
     printf("[%d] - Opening device \n", getpid() );
     fd = open( "/dev/SAMPLE_DEVIC", O_RDWR );
     printf("PID [%d]\n", getpid());
     getchar();
            
     /* write the contents of my buffer into the device */
     ret = write( fd, my_buf, 4000 );
     if(ret==-1)
     {
	     perror("ERROR");
	     exit(1);
     }
            
     /* read 70 characters from 20th character */
     lseek( fd, 20, SEEK_SET );
     ret=read( fd, my_buf, 70 );
     if(ret==-1)
     { 
	     perror("TEST");
	     printf("ERRNO:%d\n",errno);
	     exit(2);
     }

     printf("I read this from the device\n%s\n", my_buf);
     
     /* Close the device */
     close(fd);        

}
