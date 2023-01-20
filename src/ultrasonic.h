#ifndef _ULTRASONIC_H
#define _ULTRASONIC_H

#define TRIGGER1 23
#define ECHO1 24
#define TRIGGER2 25
#define ECHO2 16

#define DELAY 50    // Delay between measurements (ms)
#define TTL 1000    // Time to leave (ms)



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
 * @brief Get the Distance in centimeters, measured
 * with HC-SR04 module, connected on the specified pins.
 * 
 * @param GPIO pin number of trigger
 * @param GPIO pin number of echo
 * @return On success, positive float value of centimeters is returned.
 * On error, the value will be negative.
 */
float getDistanceCM(int trigger, int echo);

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
 * @return On success, the new count is returned. 
 * On error, -999 is returned.
 */
int updateCount(void);

#endif