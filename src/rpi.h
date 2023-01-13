#ifndef _RPI_H
#define _RPI_H

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
 * @return On success, 0 is returned. On error, -1 is returned.
 */
int digitalWrite(int pin, int value);

/**
 * @brief Checks if specified GPIO is high (3.3V) or low (0V).
 * 
 * @param GPIO pin number
 * @return int will be 1 for high and 0 for low.
 * On error, -1 will be returned.
 */
int digitalRead(int pin);

#endif