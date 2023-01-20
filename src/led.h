#ifndef _LED_H
#define _LED_H

#define GREEN 26
#define YELLOW 6
#define RED 5

/**
 * @brief Green LED is turned on.
 * 
 * @return On success, 0 is returned. On error, -1 is returned.
 */
int turnOnGreen(void);

/**
 * @brief Green LED is turned off.
 * 
 * @return On success, 0 is returned. On error, -1 is returned.
 */
int turnOffGreen(void);

/**
 * @brief Yellow LED is turned on.
 * 
 * @return On success, 0 is returned. On error, -1 is returned.
 */
int turnOnYellow(void);

/**
 * @brief Yellow LED is turned off.
 * 
 * @return On success, 0 is returned. On error, -1 is returned.
 */
int turnOffYellow(void);

/**
 * @brief Red LED is turned on.
 * 
 * @return On success, 0 is returned. On error, -1 is returned.
 */
int turnOnRed(void);

/**
 * @brief Red LED is turned off.
 * 
 * @return On success, 0 is returned. On error, -1 is returned.
 */
int turnOffRed(void);

#endif