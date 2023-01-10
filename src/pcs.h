#ifndef _PCS_H
#define _PCS_H

/**
 * @brief Pauses the program for the amount of time (in microseconds)
 * specified by the parameter. There are a thousand microseconds in a
 * millisecond and a million microseconds in a second.
 * 
 * @param microseconds 
 */
void delayUS(long microseconds);

/**
 * @brief Pauses the program for the amount of time (in milliseconds)
 * specified by the parameter. There are a thousand milliseconds in a
 * second.
 * 
 * @param milliseconds 
 */
void delayMS(long milliseconds);

/**
 * @brief Sets specified GPIO high (3.3V) or low (0V).
 * 
 * @param GPIO pin number 
 * @param value can be 1 for high and 0 for low. 
 */
void digitalWrite(int pin, int value);

/**
 * @brief Checks if specified GPIO is high (3.3V) or low (0V).
 * 
 * @param GPIO pin number
 * @return int will be 1 for high and 0 for low.
 */
int digitalRead(int pin);

#endif