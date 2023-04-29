#ifndef _BUTTON_H
#define _BUTTON_H

#include <time.h>

/**
 * @brief Check if button UP was pressed.
 * 
 * @return When Button is pressed, 1 is returned.
 * Otherwise 0. On error, -1 is returned.
 */
int buttonUP(void);

/**
 * @brief Check if button OK was pressed.
 * 
 * @return When Button is pressed, 1 is returned.
 * Otherwise 0. On error, -1 is returned.
 */
int buttonOK(void);

#endif