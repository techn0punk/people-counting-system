#include "display.h"



//#include "rpi.h"

int lcdS1(void) {

    if ((fd = open("/dev/i2c-1", O_RDWR)) < 0) return -1 ; // Check interface for device
    if (ioctl(fd, I2C_SLAVE, I2C_ADDR) < 0) return -1 ;

    lcdLoc(Line0); typeln("calibration");
	lcdLoc(Line1); typeln("keep area free");
	sleep(2);
    ClrLcd();
	sleep(1);



    return 0;
}

int lcdS2(int decimalplace, int digit) {

    return 0;
    if (decimalplace != 0 && decimalplace != 1) {
        lcdLoc(Line0); typeln("Error");//Invalid decimal. Must be 0 or 1
        return -1;
    }
    if (digit < 0 || digit > 9) {
        lcdLoc(Line0); typeln("Error");//Invalid digit. Must be between 0 and 9
        return -1;
    }
    lcdLoc(Line1); typeln("%d %d", decimalplace, digit);

 
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

    if (count < 0) {
        lcdLoc(Line0); typeln("Error"); //Invalid count. Must be greater than or equal to 0
        
        return -1;
    }
    if (limit < 1) {
        lcdLoc(Line0); typeln("Error"); //Invalid limit. Must be greater than 0
        
        return -1;
    }

    lcdLoc(Line1); typeln("%d %d", count, limit);

    
    return 0;
}

int lcdS4(void) {

    lcdLoc(Line0); typeln("want to reset ?");
    lcdLoc(Line1); typeln("UP to cancel");

    return 0;
}

int lcdSE(char *errorcause) {
    if (errorcause == NULL) {
        lcdLoc(Line0); typeln("Error");
        return -1;
    }

    if (strlen(errorcause) > 16) {
        lcdLoc(Line0); typeln("Error");//Error cause string is too long
        
        return -1;
    }

    lcdLoc(Line0); typeln("%s", errorcause);//Displaying S5 (error) menu on LCD with error cause

    
    return 0;

    
}
