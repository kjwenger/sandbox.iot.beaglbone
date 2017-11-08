/***********************************************************************
 *************************mag3110_test**********************************
 ***********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>

#include "mag3110.h"

#define CHIP_ADDR	0x0e		
#define I2C_DEV		"/dev/i2c-2"
#define DR_STATUS 	0X00		
#define XYZ_DATA 	0X01		
#define WHO_AM_I 	0X07		

int MAG3110_XOFF=0,MAG3110_YOFF=0;
int MAG3110_XMax=0,MAG3110_YMax=0,MAG3110_XMin=0,MAG3110_YMin=0;
int MAG3110_XData=0,MAG3110_YData=0;
int ang;

#if 1
void read_from_iic1(struct eeprom *e)
{
	tword wx, wy, wz; 
	static   unsigned char	First_Flag=0;
	wx.mbyte.hi = eeprom_read_byte(e, 0x01); 
	wx.mbyte.lo = eeprom_read_byte(e, 0x02);
	wy.mbyte.hi = eeprom_read_byte(e, 0x03);
	wy.mbyte.lo = eeprom_read_byte(e, 0x04); 
	wz.mbyte.hi = eeprom_read_byte(e, 0x05); 
	wz.mbyte.lo = eeprom_read_byte(e, 0x06); 
	
	// printf("X:%u  ",wx.mbyte.hi*256+wx.mbyte.lo);
	// printf("Y:%u  ",wy.mbyte.hi*256+wy.mbyte.lo);
	// printf("Z:%u  ",wz.mbyte.hi*256+wz.mbyte.lo);
	
	
	MAG3110_XData=wx.mbyte.hi*256+wx.mbyte.lo;	
	MAG3110_YData=wy.mbyte.hi*256+wy.mbyte.lo;	
	
	if (!First_Flag)
	{
		printf("undate max and min\n");
		MAG3110_XMax = MAG3110_XData;
		MAG3110_XMin = MAG3110_XData;
		MAG3110_YMax = MAG3110_YData;
		MAG3110_YMin = MAG3110_YData;
		First_Flag = 1;
	}
	if (MAG3110_XData > MAG3110_XMax)
	{
		MAG3110_XMax =  MAG3110_XData;
	}
	else if (MAG3110_XData < MAG3110_XMin)
	{
		MAG3110_XMin =  MAG3110_XData;
	}
	if (MAG3110_YData > MAG3110_YMax)
	{
		MAG3110_YMax =  MAG3110_YData;
	}
	else if (MAG3110_YData < MAG3110_YMin)
	{
		MAG3110_YMin =  MAG3110_YData;
	}
	MAG3110_XOFF = (MAG3110_XMax + MAG3110_XMin) / 2;	
	MAG3110_YOFF = (MAG3110_YMax + MAG3110_YMin) / 2;	
	
    // printf("\r\nMAG3110_XMaxd ",MAG3110_XMax);
	// printf("MAG3110_XMind\r\n",MAG3110_XMin);
    // printf("MAG3110_XOFFd\r\n",MAG3110_XOFF);

    // printf("\r\nMAG3110_YMaxd  ",MAG3110_YMax);
	// printf("MAG3110_YMind\r\n ",MAG3110_YMin);
    // printf("AG3110_YOFFd\r\n",MAG3110_YOFF);

	ang=MAG3110_DataProcess(wx.mbyte.hi*256+wx.mbyte.lo,wy.mbyte.hi*256+wy.mbyte.lo,MAG3110_XOFF,MAG3110_YOFF);
	
}
#else

static int read_from_iic1(struct eeprom *e)
{
	int ch, i;
	char tmp[6] ="";
	while(1)
	{
		if(eeprom_read_byte(e, DR_STATUS) &0x08)	
		{
			for(i = 0;i<6;i++)
			{
				tmp[i] = eeprom_read_byte(e, XYZ_DATA+i);
				
			}
			printf("_%d_%d_%d_%d_%d_%d",tmp[0],tmp[1],tmp[2],tmp[3],tmp[4],tmp[5]);
			sleep(1);
			printf("\n");
		}
	}
	printf("\n\n");	
	return 0;
}
#endif
static int init_to_iic1(struct eeprom *e, int addr)
{
	int i, ret;
	
	int data = 0x00;
	eeprom_write_byte(e, addr, data);
	
	data |= 0x04;
	eeprom_write_byte(e, addr, data);
	
	data += 1;
	eeprom_write_byte(e, addr, data);	

	return 0;
}

void check_normal(struct eeprom *e)
{
	char ret;
	if(0xc4 == eeprom_read_byte(e,WHO_AM_I))
	{
		printf("everything is OK\n");
	}
}

void  Delay(int nCount)
{
  for(; nCount != 0; nCount--);
}

int main(int argc, char** argv)
{
	struct eeprom e;
	tword wx,wy,wz;		
	int opt = 0;
	int ret = 0;

	if ((ret = eeprom_open(I2C_DEV, CHIP_ADDR, &e)) < 0)
	{
		printf("unable to open eeprom device file\n");
		exit(0);
	}
	
	check_normal(&e);
	
	printf(" init_mag3110 \n");
	init_to_iic1(&e, 16);		
	
	printf(" Reading xyz data from mag3110\n");

	while(1)
	{	
		Delay(0xfffff);
		Delay(0xfffff);
		Delay(0xfffff);
		Delay(0xfffff);
		Delay(0xfffff);
		Delay(0xfffff);
		
		if(eeprom_read_byte(&e, DR_STATUS) & 0x08)	
		{ 
			read_from_iic1(&e); 
			/*The data needs to be calibrated, turning a lap*/;	
			printf("\r\nPoint to the south angle----> %d",ang);	;
		}
		else 
		{
			printf("ID Failed!\n"); 
		}	
	}
	
	eeprom_close(&e);
	
	return 0;
} 

