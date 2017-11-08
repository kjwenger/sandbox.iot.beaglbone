/*
*ds18b20 test
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/fcntl.h>

int main(int argc, char *argv[])
{
	int fd = -1, ret;
	char *tmp1, tmp2[10], ch='t';
	char devname_head[37] = "/sys/devices/w1_bus_master1/28-00000";
	char devname_end[10] = "/w1_slave";
	char dev_name[100];
	long value;
	int integer, decimal;
	char buffer[100];
	int i,j;
	
	if(argc < 2)
	{
		printf("Please input like this: 'test_ds18b20 57c5948(or other)'\nPlease see the path:/sys/bus/w1/devices/28-00000xxxxxxx/w1_slave\n");
		exit(1);
	}
	else
	{
		strcpy(dev_name, devname_head);
		strcat(dev_name, argv[1]);
		strcat(dev_name, devname_end);
	}
	
	if ((fd = open(dev_name, O_RDONLY)) < 0)
	{
		perror("open error");
		exit(1);
	}

	ret = read(fd, buffer, sizeof(buffer));
	if (ret < 0)
	{
		perror("read error");
		exit(1);
	}	

	tmp1 = strchr(buffer, ch);		
	sscanf(tmp1, "t=%s", tmp2);
	
	value = atoi(tmp2);	
	integer = value / 1000;
	decimal = value % 1000;
	
	printf("temperature is %d.%d\n", integer, decimal);

	close(fd);
	return 0;
}

