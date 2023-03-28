#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <string.h>
#include <linux/i2c-dev.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include "display.h"
#include "rpi.h"


int dfd;

char text0[17];
char text1[17];

int display = 0;

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
	write(dfd, b, 6);
    usleep(2000);
}

// clr lcd go home loc 0x80
void ClrLcd(void)   {
	lcd_wbyte(0x01, 0); // is the command to clear the display
	usleep(2000); // after each sent command, it is stopped for 2000 microseconds, is necessary,
		      // so the LCD has enough time to process the command before sending the next one
	lcd_wbyte(0x02, 0); //Return-Home-Befehl, this command tells the LCD to move the cursor to the home position
	
  
}

// Initialise display to 4 bit as per the datasheet
int lcd_init()   
{
    if ((dfd = open("/dev/i2c-1", O_RDWR)) < 0) return -1 ; // Check interface for device
    if (ioctl(dfd, I2C_SLAVE, I2C_ADDR) < 0) return -1 ;

	const uint8_t b[4] = {0x30, 0x30 | LCD_ENABLE, 0x30}; // Sequence to clock 3 into upper 4 bits
	write(dfd, b, 3);  usleep(6000); write(dfd, b, 3);  // Prepare for 4 bit width?
	lcd_wbyte(0x32, 0); // Force 4 bit width
	lcd_wbyte(0x06, 0); // Cursor move direction
	lcd_wbyte(0x0C, 0); // 0x0F On, Blink Off
	lcd_wbyte(0x28, 0); // Data length, number of lines, font size
	ClrLcd();

    display = 1;

	return 0;
}


//Exampel for LCD_DAT output to the LCD-Display
// out char to LCD at current position
void typeChar(char val)   { lcd_wbyte(val, LCD_DAT); }

// this allows use of any size string
// Could consider making this quicker by turning it into a single I2C write
void typeln(const char *st)   { while ( *st ) lcd_wbyte(*(st++), LCD_DAT); }

// go to location on LCD
void lcdLoc(int line)   { lcd_wbyte(line, 0); }

int lcdS1(void) {
    if (!display) lcd_init();
    ClrLcd();

    lcdLoc(Line0); typeln("calibration");
	lcdLoc(Line1); typeln("keep area free");

    return 0;
}

int lcdS2(int decimalplace, int limit) {
    if (!display) lcd_init();
    ClrLcd();

    if (decimalplace == 0 && limit < 10)
    {
        sprintf(text0, "         V");
        sprintf(text1, "limit = _%d", limit);
    }
    else if (decimalplace == 0 && limit >= 10)
    {
        sprintf(text0, "         V");
        sprintf(text1, "limit = %d", limit);        
    }
    else if (decimalplace == 1)
    {
        sprintf(text0, "        V");
        sprintf(text1, "limit = %d", limit);
    }
    else //Invalid decimal. Must be 0 or 1
    {
        return -1;
    }

    lcdLoc(Line0); typeln(text0);
    lcdLoc(Line1); typeln(text1);

    return 0;
}

/**
 * int lcdS2(int decimalplace, int digit) {
    int limit = digit;
    int cursor = decimalplace;
    int button;
    while (1) {
        // display limit on the LCD with cursor at the current decimal place
        displayNumberWithCursor(limit, cursor);

        // get button press
        button = getButtonPress();

        // check button press
        if (button == UP) {
            int temp = limit / (int)pow(10, cursor) % 10;
            temp = (temp + 1) % 10;
            limit += temp * (int)pow(10, cursor);
        } else if (button == OK) {
            return limit;
        } else if (button == DOWN) {
            int temp = limit / (int)pow(10, cursor) % 10;
            temp = (temp - 1) % 10;
            limit += temp * (int)pow(10, cursor);
        } else if (button == LEFT) {
            if (cursor > 0) {
                cursor--;
            }
        } else if (button == RIGHT) {
            if (cursor < 1) {
                cursor++;
            }
        }
    }
    return -1;
}
*/

int lcdS3(int count, int limit) {
    if (!display) lcd_init();
    ClrLcd();

    // if (count < 0) {
    //     return -1;
    // }
    // if (limit < 1) {
    //     return -1;
    // }

    sprintf(text0, "count = %d/%d", count, limit);
    sprintf(text1, "any key for rst");

    lcdLoc(Line0); typeln(text0);
    lcdLoc(Line1); typeln(text1);

    
    return 0;
}

int lcdS4(void) {
    if (!display) lcd_init();
    ClrLcd();

    lcdLoc(Line0); typeln("want to reset ?");
    lcdLoc(Line1); typeln("UP to cancel");

    return 0;
}

int lcdSE(char *errorcause) {
    if (!display) lcd_init();
    ClrLcd();

    if (strlen(errorcause) > 16) {
        return -1;
    }

    sprintf(text0, "Error:");
    sprintf(text1, errorcause);

    lcdLoc(Line0); typeln(text0);
    lcdLoc(Line1); typeln(text1);
    
    return 0;
}
