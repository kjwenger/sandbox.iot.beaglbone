/***********************************************************************
 **************************pwm_test*************************************
 ***********************************************************************/
#include <stdio.h>
#include <stdlib.h>	
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <string.h>

int main(int argc, char *argv[])
{
	int fd;
	int i;
	int ret;
	int length;	
	char devname_head[37] = "/sys/devices/ocp.3/pwm_ehrpwm1b.";
	char devname_end[10] = "/duty";
	char dev_name[100];

	char* w_buffer[] = {"500000","500000","500000","0","500000","500000","500000","0",
						"500000","500000","500000","0","500000","500000","500000","0",
						"500000","500000","500000","0","500000","500000","500000","0"};

	if(argc < 2)
	{
		printf("Please input like this: 'test_pwm 14(or other)'\nPlease see the path:/sys/devices/ocp.3/pwm_ehrpwm1b.x/duty\n");
		exit(1);
	}
	else
	{
		strcpy(dev_name, devname_head);
		strcat(dev_name, argv[1]);
		strcat(dev_name, devname_end);
	}
	
	fd = open(dev_name,O_RDWR);
	if(fd < 0)
	{
		perror("can not open device");
		exit(1);
	}

	length = sizeof(w_buffer)/sizeof(w_buffer[0]);
	for(i=0;i<length;i++)
	{
		ret = write(fd,w_buffer[i],6);
		if (ret < 0)
		{
			perror("write error");
			exit(1);
		}

		printf("frequency is -----> %s\n",w_buffer[i]);
		
		usleep(200*400);
	}

	close(fd);
	return 0;
}

