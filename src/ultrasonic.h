#ifndef _ULTRASONIC_H
#define _ULTRASONIC_H

/**
 * @brief Holds the count of people currently in the room.
 * 
 */
extern int count;

/**
 * @brief Holds the distance in cm below which an object
 * is detected. (Valid for sensor 1)
 * 
 */
extern float threshold_distance1;

/**
 * @brief Holds the distance in cm below which an object
 * is detected. (Valid for sensor 2)
 * 
 */
extern float threshold_distance2;

/**
 * @brief Calibrates the ultrasonic sensors to the
 * distance to the wall and determines at which
 * distance an object is detected in the measuring
 * area. During the runtime of this function, no
 * one may be present in the measuring area.
 * 
 * @param threshold value as a proportion of 1 below
 * which an object is detected. (e.g. 0.9 or 0.75)
 * @return On success, 0 is returned. On error, -1 is returned.
 */
int calibrate(float threshold);

/**
 * @brief Updates the count variable depending on
 * whether people enter or leave the room.
 * This function is non-blocking.
 * 
 * @return On success, the new count is returned. On error, -1 is returned.
 */
int updateCount(void);

#endif