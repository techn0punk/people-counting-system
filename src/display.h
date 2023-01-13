#ifndef _DISPLAY_H
#define _DISPLAY_H

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
 * @param digit to set on the specified decimalplace. Can be 0 to 9.
 * @return On success, 0 is returned. On error, -1 is returned.
 */
int lcdS2(int decimalplace, int digit);

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