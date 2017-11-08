/**********************************************
 **************leds test***********************
***********************************************/
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/stat.h>
#include<fcntl.h>

char dev_name[50];
char* w_buffer[] = {"1","0"};
	
int main(int argc,char *argv[]) 
{
	int fd;
	int ret;
	int i;

	/*turn off all leds*/
	for(i=1;i<5;i++)
	{
		sprintf(dev_name, "/sys/class/leds/led%d/brightness\0", i);
		
		fd = open(dev_name,O_RDWR);
		if(fd < 0)
		{
			perror("open error");
			exit(1);
		}
		
		/*turn off the led*/
		ret = write(fd, w_buffer[1], 4);
		if(ret < 0)
		{
			perror("write error\n");
			exit(1);
		}
		
		close(fd);
	}
	
	while(1)
	{		
		
		for(i=1;i<5;i++)
		{
			sprintf(dev_name, "/sys/class/leds/led%d/brightness\0", i);
			
			fd = open(dev_name,O_RDWR);
			if(fd < 0)
			{
				perror("open error");
				exit(1);
			}

			/*turn on the led*/
			ret = write(fd, w_buffer[0], 4);
			if(ret < 0)
			{
				perror("write error\n");
				exit(1);
			}
			
			printf("led open ---------> %d\n",i);
			usleep(400*400);

			/*turn off the led*/
			ret = write(fd, w_buffer[1], 4);
			if(ret < 0)
			{
				perror("error to write\n");
				exit(1);
			}
			
			close(fd);
		}
	}	
	return 0;
}

