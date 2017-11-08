#ifndef __EEPROM_H_
#define __EEPROM_H_
#include <linux/i2c-dev.h>
#include <linux/i2c.h>

struct eeprom
{
	char *dev; 	// device file i.e. /dev/i2c-N
	int addr;	// i2c address
	int fd;		// file descriptor
	int type; 	// eeprom type
};

typedef union
{
  unsigned int mword;
  struct
  {
    unsigned char hi;	
    unsigned char lo;	
  }mbyte;
}tword; 


int eeprom_open(char *dev_name, int addr, struct eeprom*);

int eeprom_close(struct eeprom *e);

int eeprom_read_byte(struct eeprom* e, __u16 mem_addr);

int eeprom_write_byte(struct eeprom *e, __u16 mem_addr, __u8 data);

int MAG3110_DataProcess (int MAG3110_XData,int MAG3110_YData,int MAG3110_XOFF,int MAG3110_YOFF);
#endif  //__EEPROM_H_

