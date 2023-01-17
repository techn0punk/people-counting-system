#ifndef _DISTANCE_H
#define _DISTANCE_H

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
 * @brief Puts a high Pulse on the given Pin for the given amount of time.
 * 
 * @param pin 
 * @param microseconds 
 */
void putPulse(int pin, long microseconds);

/**
 * @brief This measures the duration (in microseconds) 
 * of a high pulse on the given pin.
 * 
 * @param pin number 24
 * @return float microseconds
 */
float getPulseUS(int pin);

/**
 * @brief Measures distance (in centimeters) with an HC-SR04 ultrasonic
 * module.
 * 
 * @param trigger Pin of HC-SR04
 * @param echo Pin of HC-SR04
 * @return float distance in centimeters
 */
float getDistanceCM(int trigger, int echo);

#endif