/*************************************************************
 *************************spi_test****************************
**************************************************************/
#include <stdint.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/types.h>
#include <linux/spi/spidev.h>

#define ARRAY_SIZE(a) (sizeof(a) / sizeof((a)[0]))

static void pabort(const char *s)
{
	perror(s);
	abort();
}

static const char *device = "/dev/spidev1.1";
static uint8_t mode=3;
static uint8_t bits = 8;
static uint32_t speed = 50000;
static uint16_t delay;

int fd;
int fd_cs;
int ret = 0;
int pullup = 1;
int pulldown = 2;

void _delay_ms( unsigned int x)
{
    unsigned int  i,j;
    for(i=0;i<x;i++)
       for(j=0;j<100;j++);
}

void ee_write(unsigned int BufferOffset,unsigned char data)
{
	//cs=0;
	ret = write(fd_cs, &pulldown, 4);
	if(ret < 0)
	{
		perror("error to write\n");
		exit(1);
	}

    //spi_transmit_byte(0x84);	
	uint8_t txb[1] = {
		0x84,
	};
	ret = write(fd,txb,ARRAY_SIZE(txb));
	if (ret <1)
		pabort("can't write");
	
	//spi_transmit_byte(0xff);		
	txb[0] = 0xff;
	ret = write(fd,txb,ARRAY_SIZE(txb));
	if (ret <1)
		pabort("can't write");
   
    //spi_transmit_byte((unsigned char)(BufferOffset>>8));  
	txb[0] = (unsigned char)(BufferOffset>>8);
	ret = write(fd,txb,ARRAY_SIZE(txb));
	if (ret <1)
		pabort("can't write");
		
	//spi_transmit_byte((unsigned char)BufferOffset);		
	txb[0] = (unsigned char)BufferOffset;
	ret = write(fd,txb,ARRAY_SIZE(txb));
	if (ret <1)
		pabort("can't write");
		
	//spi_transmit_byte(data);		        	
	txb[0] = data;
	ret = write(fd,txb,ARRAY_SIZE(txb));
	if (ret <1)
		pabort("can't write");	  
	  													
    //cs=1;
	ret = write(fd_cs, &pullup, 4);
	if(ret < 0)
	{
		perror("error to write\n");
		exit(1);
	}
}

unsigned char ee_read(unsigned int BufferOffset)
{
	uint8_t txb[1] = {
		0,
	};
	uint8_t rxb[ARRAY_SIZE(txb)] = {0, 
	};   

	//cs=0;
	ret = write(fd_cs, &pulldown, 4);
	if(ret < 0)
	{
		perror("error to write\n");
		exit(1);
	}
	
	//spi_transmit_byte(0xD4);	
	txb[0] = 0xD4;
	ret = write(fd,txb,ARRAY_SIZE(txb));
	if (ret <1)
		pabort("can't write");
	
	//spi_transmit_byte(0xff);
	txb[0] = 0xff;
	ret = write(fd,txb,ARRAY_SIZE(txb));
	if (ret <1)
		pabort("can't write");
     
    //spi_transmit_byte((unsigned char)(BufferOffset>>8));   
	txb[0] = (unsigned char)(BufferOffset>>8);
	ret = write(fd,txb,ARRAY_SIZE(txb));
	if (ret <1)
		pabort("can't write"); 
		
	//spi_transmit_byte((unsigned char)BufferOffset);	
	txb[0] = (unsigned char)BufferOffset;
	ret = write(fd,txb,ARRAY_SIZE(txb));
	if (ret <1)
		pabort("can't write");
	
	//spi_transmit_byte(0xff);	
	txb[0] = 0xff;
	ret = write(fd,txb,ARRAY_SIZE(txb));
	if (ret <1)
		pabort("can't write");

	//spi_transmit_byte(0xff);
	ret = read(fd,rxb,ARRAY_SIZE(txb));
	if (ret <1)
		pabort("can't read");
		
	//cs=1;
	ret = write(fd_cs, &pullup, 4);
	if(ret < 0)
	{
		perror("error to write\n");
		exit(1);
	} 		

    //temp=SSPBUF;	
 	return rxb[0];	
}


int main(int argc, char *argv[])
{
	unsigned int i, num;

	fd_cs = open("/dev/ctl_io",O_RDWR);
	if(fd_cs < 0)
	{
		perror("open error");
		exit(1);
	}
	
	fd = open(device, O_RDWR);
	if (fd < 0)
		pabort("can't open device");

	/*
	 * spi mode
	 */
	ret = ioctl(fd, SPI_IOC_WR_MODE, &mode);
	if (ret == -1)
		pabort("can't set spi mode");

	ret = ioctl(fd, SPI_IOC_RD_MODE, &mode);
	if (ret == -1)
		pabort("can't get spi mode");

	/*
	 * bits per word
	 */
	ret = ioctl(fd, SPI_IOC_WR_BITS_PER_WORD, &bits);
	if (ret == -1)
		pabort("can't set bits per word");

	ret = ioctl(fd, SPI_IOC_RD_BITS_PER_WORD, &bits);
	if (ret == -1)
		pabort("can't get bits per word");

	/*
	 * max speed hz
	 */
	ret = ioctl(fd, SPI_IOC_WR_MAX_SPEED_HZ, &speed);
	if (ret == -1)
		pabort("can't set max speed hz");

	ret = ioctl(fd, SPI_IOC_RD_MAX_SPEED_HZ, &speed);
	if (ret == -1)
		pabort("can't get max speed hz");
	printf("spi mode: %d\n", mode);
	printf("bits per word: %d\n", bits);
	printf("max speed: %d Hz (%d KHz)\n", speed, speed/1000);

	//cs=1 
	ret = write(fd_cs, &pullup, 4);
	if(ret < 0)
	{
	   perror("error to write\n");
	   exit(1);
	}
	
	sleep(1);

 /* Write and  read */
	printf(">>>>>>>>Start to write [0-255]<<<<<<<<<\n");
	for(num=0;num<256;num++)
	{
		ee_write((unsigned int)num,num);
		printf("%d  ",num);
		for(i=0;i<40;i++);				
	}

  	printf("\n");
	printf(">>>>>>>>Start to read [0-255]<<<<<<<<<\n");
	
	for(num=0;num<256;num++)
	{
		printf("%d  ",ee_read((unsigned int)num));
		_delay_ms(50);
	}
 	printf("\n");	

	close(fd);
	close(fd_cs);

	return ret;
}

