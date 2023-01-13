#ifndef _BUTTON_H
#define _BUTTON_H

#include <time.h>

/**
 * @brief Computer core time when UP was last pressed.
 * 
 */
extern clock_t last_UP;

/**
 * @brief Computer core time when OK was last pressed.
 * 
 */
extern clock_t last_OK;

/**
 * @brief Number of milliseconds that must have passed
 * before a new button press should be recognized.
 * 
 */
extern int debounce_MS;

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