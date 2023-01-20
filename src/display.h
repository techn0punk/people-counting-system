#ifndef _DISPLAY_H
#define _DISPLAY_H

// I2C device address
#define I2C_ADDR   0x27 


#define Line0  0x80
#define Line1  0xC0


#define LCD_DAT         0b00000001  // Sending data bit on bit off cmd
#define LCD_READ        0b00000010  // Set bit to assert read line
#define LCD_ENABLE      0b00000100  // Enable bit toggle to latch data
#define LCD_BACKLIGHT   0b00001000  // Set bi to turn backlight on 

/**
 * @brief display file descriptor seen by all subroutines
 * 
 */
extern int dfd;

/**
 * @brief here is the text stored for each display line
 * 
 */
extern char text0[17];
extern char text1[17];

/**
 * @brief 1 if display was initialized. 0 if not.
 * 
 */
extern int display;

/**
 * @brief Show S1 (calibration) menu on display.
 * 
 * @return On success, 0 is returned. On error, -1 is returned.
 */
int lcdS1(void);

/**
 * @brief Show S2 (set limit) menu on display.
 * 
 * @param decimalplace determines over which decimal place
 * the cursor ('V') is shown. Can be 0 for ones digit  (10^0)
 * or 1 for tens digit (10^1).
 * @param limit that is to be set
 * @return On success, 0 is returned. On error, -1 is returned.
 */
int lcdS2(int decimalplace, int limit);

/**
 * @brief Show S3 (counting) menu on display.
 * 
 * @param count is the number before the '/'
 * @param limit is the number after the '/'
 * @return On success, 0 is returned. On error, -1 is returned.
 */
int lcdS3(int count, int limit);

/**
 * @brief Show S4 (reset) menu on display.
 * 
 * @return On success, 0 is returned. On error, -1 is returned.
 */
int lcdS4(void);

/**
 * @brief Show S5 (error) menu on display.
 * 
 * @param errorcause can be a string of max 16 characters.
 * @return On success, 0 is returned. On error, -1 is returned.
 */
int lcdSE(char *errorcause);


#endif