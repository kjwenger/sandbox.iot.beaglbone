#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <linux/fs.h>
#include <sys/types.h>
#include <sys/ioctl.h>
#include <errno.h>
#include <assert.h>
#include <string.h>
#include <math.h>

#include "mag3110.h"


int MAG3110_DataProcess (int MAG3110_XData,int MAG3110_YData,int MAG3110_XOFF,int MAG3110_YOFF)
{


	int MAG3110_Ang;

	MAG3110_XData -= MAG3110_XOFF;
	MAG3110_YData -= MAG3110_YOFF;
	if (MAG3110_XData == 0)
	{
		if (MAG3110_YData>0)
		{
			MAG3110_Ang = 90;
		}
		else
		{
			MAG3110_Ang = 270;
		}
	}
	else if (MAG3110_YData == 0)
	{
		if (MAG3110_XData>0)
		{
			MAG3110_Ang = 0;
		}
	else
	{
		MAG3110_Ang = 180;
	}
	}
	else if ((MAG3110_XData > 0) && (MAG3110_YData > 0))
	{
		MAG3110_Ang = ( ( ( (float)MAG3110_YData) / ( (float) MAG3110_XData ) ) ) * 180 / 3.14;
	}
	else if ((MAG3110_XData < 0) && (MAG3110_YData > 0))
	{
		MAG3110_XData = -MAG3110_XData;
		MAG3110_Ang = 180 - ( ( ( (float)MAG3110_YData) / ( (float) MAG3110_XData ) ) ) * 180 / 3.14;
	}
	else if ((MAG3110_XData < 0) && (MAG3110_YData < 0))
	{
		MAG3110_XData = -MAG3110_XData;
		MAG3110_YData = -MAG3110_YData;
		MAG3110_Ang = ( ( ( (float)MAG3110_YData) / ( (float) MAG3110_XData ) ) ) * 180 / 3.14 + 180;
	}
	else if ((MAG3110_XData > 0) && (MAG3110_YData < 0))
	{
		MAG3110_YData = -MAG3110_YData;
		MAG3110_Ang = 360 -( ( ( (float)MAG3110_YData) / ( (float) MAG3110_XData ) ) ) * 180 / 3.14;
	}

	return 	 MAG3110_Ang;
}

static inline __s32 i2c_smbus_access(int file, char read_write, __u8 command, int size, union i2c_smbus_data *data)
{
	struct i2c_smbus_ioctl_data args;

	args.read_write = read_write;
	args.command = command;
	args.size = size;
	args.data = data;
	
	return ioctl(file, I2C_SMBUS, &args);
}

int eeprom_read_byte(struct eeprom* e, __u16 mem_addr)
{
	int r;
	union i2c_smbus_data data;

	ioctl(e->fd, BLKFLSBUF);  //clear kernel read buffer

	__u8 buf =  mem_addr & 0x0ff;
	r = i2c_smbus_access(e->fd, I2C_SMBUS_WRITE, buf, I2C_SMBUS_BYTE, NULL);
	
	if (r < 0)
		return r;
	if (i2c_smbus_access(e->fd, I2C_SMBUS_READ, 0, I2C_SMBUS_BYTE, &data))
		return -1;
	else
		return 0x0FF & data.byte;
}

int eeprom_write_byte(struct eeprom *e, __u16 mem_addr, __u8 data)
{
	int r;
	__u8 command = mem_addr & 0x00ff;
	union i2c_smbus_data i2c_data;

	i2c_data.byte = data;
	r = i2c_smbus_access(e->fd, I2C_SMBUS_WRITE, command, I2C_SMBUS_BYTE_DATA, &i2c_data);

/*	
	if(r < 0)
		printf("IIC write error");
*/
	usleep(10);

	return r;
}

int eeprom_open(char *dev_name, int addr, struct eeprom* e)
{
	int funcs, fd, r;
	e->fd = e->addr = 0;
	e->dev = 0;

	fd = open(dev_name, O_RDWR);
	if(fd <= 0)
	{
		fprintf(stderr, "Error eeprom_open: %s\n", strerror(errno));
		return -1;
	}

	
	
#if 1
	// get funcs list
	if((r = ioctl(fd, I2C_FUNCS, &funcs) < 0))
	{
		fprintf(stderr, "Error eeprom_open: %s\n", strerror(errno));
		return -1;
	}
#endif
	// check for req funcs
	/*CHECK_I2C_FUNC(funcs, I2C_FUNC_SMBUS_READ_BYTE);
	CHECK_I2C_FUNC(funcs, I2C_FUNC_SMBUS_WRITE_BYTE);
	CHECK_I2C_FUNC(funcs, I2C_FUNC_SMBUS_READ_BYTE_DATA);
	CHECK_I2C_FUNC(funcs, I2C_FUNC_SMBUS_WRITE_BYTE_DATA);
	CHECK_I2C_FUNC(funcs, I2C_FUNC_SMBUS_READ_WORD_DATA);
	CHECK_I2C_FUNC(funcs, I2C_FUNC_SMBUS_WRITE_WORD_DATA);*/

	// set working device
	if ((r = ioctl(fd, I2C_SLAVE, addr)) < 0)
	{
		fprintf(stderr, "Error eeprom_open: %s\n", strerror(errno));
		return -1;
	}
	e->fd = fd;
	e->addr = addr;
	e->dev = dev_name;
	
	return 0;
}

int eeprom_close(struct eeprom *e)
{
	close(e->fd);
	e->fd = -1;
	e->dev = 0;
	
	return 0;
}

