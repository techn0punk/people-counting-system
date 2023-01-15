#ifndef _HEADER_H
#define _HEADER_H
#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <linux/i2c-dev.h>
#include <fcntl.h>
#include <sys/ioctl.h>




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

/////////////////////////////

const char *buttonPath = "/sys/class/gpio/gpio17/value";

void exportPin_UP(int pin){
    int exportFile = open("/sys/class/gpio/export", O_WRONLY);
    char buffer[3];
    int len = snprintf(buffer, sizeof(buffer), "%d", pin);
    write(exportFile, buffer, len);
    close(exportFile);
}

void setPinDirection_UP(int pin,const char *direction){
    char path[35];
    snprintf(path, sizeof(path), "/sys/class/gpio/gpio%d/direction", pin);
    int directionFile = open(path, O_WRONLY);
    write(directionFile, direction, 2);
    close(directionFile);
}

int readPinValue_UP(int pin){
    char path[35];
    snprintf(path, sizeof(path), "/sys/class/gpio/gpio%d/value", pin);
    int valueFile = open(path, O_RDONLY);
    char value;
    read(valueFile, &value, 1);
    close(valueFile);
    return (value == '0');
}
////////////////////////////OK
void exportPin_OK(int pin){
    int exportFile = open("/sys/class/gpio/export", O_WRONLY);
    char buffer[3];
    int len = snprintf(buffer, sizeof(buffer), "%d", pin);
    write(exportFile, buffer, len);
    close(exportFile);
}


void setPinDirection_OK(int pin,const char *direction){
    char path[35];
    snprintf(path, sizeof(path), "/sys/class/gpio/gpio%d/direction", pin);
    int directionFile = open(path, O_WRONLY);
    write(directionFile, direction, 2);
    close(directionFile);
}


int readPinValue_OK(int pin){
    char path[35];
    snprintf(path, sizeof(path), "/sys/class/gpio/gpio%d/value", pin);
    int valueFile = open(path, O_RDONLY);
    char value;
    read(valueFile, &value, 1);
    close(valueFile);
    return (value == '0');
}
////////////////////////////////////


int lcdS1()
{
    if ((fd = open("/dev/i2c-1", O_RDWR)) < 0) return -1 ; // Check interface for device
    if (ioctl(fd, I2C_SLAVE, I2C_ADDR) < 0) return -1 ;

	lcd_init();

        lcdLoc(Line0); typeln("calibration");
	lcdLoc(Line1); typeln("keep area free");
	   	sleep(2);
    	ClrLcd();
	sleep(1);
   
 
    return 0;
}

int lcdS4(void)
{
    
    exportPin_UP(17);
    setPinDirection_UP(17,"in");

    exportPin_OK(27);
    setPinDirection_OK(27,"in");

   // while(1) {
        if(readPinValue_UP(17) && readPinValue_OK(27)){
            lcdLoc(Line0); typeln("press any key");
        }
	else{
	//	sleep(3);
		lcdLoc(Line1); typeln("thk");
	
        
   // }

	return 0;
}


int lcdS2(void)
{
    exportPin_UP(17);
    setPinDirection_UP(17,"in");

    exportPin_OK(27);
    setPinDirection_OK(27,"in");
    char counter = 0;

    while(1) {
        if(readPinValue_UP(17)){
//           counter++;
           lcdLoc(Line0); typeln("1");

        }
	else{
	lcdLoc(Line0); typeln("2");
     }   
    }
    
}

#endif


