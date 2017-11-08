/*********************************************************************
 ****************************adc_test*********************************
 *********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/fcntl.h>

int main(int argc, char *argv[])
{
	int fd,ret,i;
	int adc_ch,value;
	char buffer[10];
	char dev_name[50];

	if(argc < 2)
	{
		printf("Please input Channel number,for exmaple 'test_adc 5(or 6)'\n");
		exit(1);
	}
	else
	{
		adc_ch = atoi(argv[1]);
	}

	while(1)
	{		
		sprintf(dev_name, "/sys/bus/iio/devices/iio:device0/in_voltage%d_raw",adc_ch);
		
		fd = open(dev_name,O_RDONLY);
		if(fd < 0)
		{
			perror("open error");
			exit(1);
		}

		ret = read(fd,buffer,4);
		if (ret < 0)
		{
			perror("read error");
			exit(1);
		}

		value = atoi(buffer);
		printf("Channel %d current value is %d\n",adc_ch,value);

		usleep(200*400);	
		
		close(fd);	
	}		
	return 0;
}

