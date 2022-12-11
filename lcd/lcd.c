// test program 

#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <linux/i2c-dev.h>

// I2C device address
#define I2C_ADDR   0x3F 


#define Line0  0x80
#define Line1  0xC0


#define LCD_DAT         0b00000001  
#define LCD_READ        0b00000010  
#define LCD_ENABLE      0b00000100  
#define LCD_BACKLIGHT   0b00001000  


int fd;  


void lcd_wbyte(int bits, int mode)  
{
	uint8_t b[8];  
	b[0] = b[1] = b[2] = mode | LCD_BACKLIGHT | (bits & 0xF0);
	b[1] |= LCD_ENABLE; b[2] &= ~LCD_ENABLE;
	b[3] = b[4] = b[5] = mode | LCD_BACKLIGHT | ((bits << 4) &0xF0);
	b[4] |= LCD_ENABLE; b[5] &= ~LCD_ENABLE;
	write(fd, b, 6);
}

// clr lcd go home loc 0x80
void ClrLcd(void)   {
  
}

// Initialise display to 4 bit as per the datasheet
void lcd_init()   
{
	const uint8_t b[4] = {0x30, 0x30 | LCD_ENABLE, 0x30}; // Sequence to clock 3 into upper 4 bits
	//.
	//.
	//.
}

// out char to LCD at current position
void typeChar(char val)   { lcd_wbyte(val, LCD_DAT); }

// this allows use of any size string
// Could consider making this quicker by turning it into a single I2C write
void typeln(const char *st)   { while ( *st ) lcd_wbyte(*(st++), LCD_DAT); }

// go to location on LCD
void lcdLoc(int line)   { lcd_wbyte(line, 0); }

int main()   
{
  if ((fd = open("/dev/i2c-1", O_RDWR)) < 0) return -1 ; // Check interface for device
  if (ioctl(fd, I2C_SLAVE, I2C_ADDR) < 0) return -1 ;
  lcd_init(); // setup LCD
  while (1)   
  {
  	//.
  	//.
  	//.
	sleep(1);
  }
  return 0;
}

