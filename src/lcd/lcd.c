// test program 

#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <linux/i2c-dev.h>

// I2C device address
#define I2C_ADDR   0x3F 


#define Line0  0x80
#define Line1  0xC0


#define LCD_DAT         0b00000001  // Sending data bit on bit off cmd
#define LCD_READ        0b00000010  // Set bit to assert read line
#define LCD_ENABLE      0b00000100  // Enable bit toggle to latch data
#define LCD_BACKLIGHT   0b00001000  // Set bi to turn backlight on 

//// file descriptor seen by all subroutines
int fd;  

//write byte to LCD in one IIC transaction
//The bits argument specifies the byte of data that will be written to the LCD screen
//the mode argument specifies the mode in which the data will be written to the screen.
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
	lcd_wbyte(0x01, 0); // is the command to clear the display
	usleep(2000); // after each sent command, it is stopped for 2000 microseconds, is necessary,
		      // so the LCD has enough time to process the command before sending the next one
	lcd_wbyte(0x02, 0); //Return-Home-Befehl, this command tells the LCD to move the cursor to the home position
	
  
}

// Initialise display to 4 bit as per the datasheet
void lcd_init()   
{
	const uint8_t b[4] = {0x30, 0x30 | LCD_ENABLE, 0x30}; // Sequence to clock 3 into upper 4 bits
	write(fd, b, 3);  usleep(6000); write(fd, b, 3);  // Prepare for 4 bit width?
	lcd_wbyte(0x32, 0); // Force 4 bit width
	lcd_wbyte(0x06, 0); // Cursor move direction
	lcd_wbyte(0x0C, 0); // 0x0F On, Blink Off
	lcd_wbyte(0x28, 0); // Data length, number of lines, font size
	ClrLcd();
	
}


//Exampel for LCD_DAT output to the LCD-Display
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
  	//the function "lcdLoc()" to set the cursor to a specific location on the LCD screen
  	//the function "typenln()" to write the specified text to that location on the LCD screen
  	//the funktion "sleep()" to pause the program for specified number os seconds
  	//the function "ClrLcd()" to clear the LCD screen
  	lcdLoc(Line0); typeln("Raw IIC write");
    	lcdLoc(Line1+1); typeln("Line 1");
    	sleep(2);
    	ClrLcd();
	sleep(1);
  }
  return 0;
}

