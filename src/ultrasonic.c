#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <time.h>
#include <stdio.h>
#include <sys/ioctl.h>
#include <sys/epoll.h>
#include <linux/gpio.h>
#include "rpi.h"
#include "ultrasonic.h"

int count;
int last_count;

float threshold_distance1;
float threshold_distance2;

float getDistanceCM(int trigger, int echo) {
    putPulse(trigger, 10);
    float us = getPulseUS(echo);
    if (us < 0.0f)
    {
        return -1.0f;
    }
    
    return us / 58;
}

int calibrate(float threshold) {
    count = 0;
    last_count = 0;

    float d1_base_level = 0.0;
    float d2_base_level = 0.0;
    float d1, d2;

    for (size_t i = 0; i < 10; i++)
    {
        d1 = getDistanceCM(TRIGGER1, ECHO1);
        if (d1 < 0.0) return -1;
        d1_base_level += d1;

        d2 = getDistanceCM(TRIGGER2, ECHO2);
        if (d2 < 0.0) return -1;
        d2_base_level += d2;
    }

    d1_base_level = d1_base_level / 10.0;
    d2_base_level = d2_base_level / 10.0;

    threshold_distance1 = d1_base_level * threshold;
    threshold_distance2 = d2_base_level * threshold;

    return 0;
}

int updateCount(void) {
    float d1 = getDistanceCM(TRIGGER1, ECHO1);
    if (d1 < 0.0) return -999;

    float d2 = getDistanceCM(TRIGGER2, ECHO2);
    if (d2 < 0.0) return -999;

    #ifdef DEBUG
    printf("CNT: %d  D1: %.2f [%.2f]  D2: %.2f [%.2f]\n", 
        count, d1, threshold_distance1, d2, threshold_distance2);
    #endif

    if (d1 < threshold_distance1) // assuming --- ltr -->
    {
        #ifdef DEBUG
        printf("D1 sensed, Waiting for D2\n");
        #endif

        for (size_t i = 0; i < SECONDSENSOR; i++) // wait ~2.5sec to confirm
        {
            d2 = getDistanceCM(TRIGGER2, ECHO2); // error happens here

            #ifdef DEBUG
            printf("D2: %.2f [%.2f]\n", d2, threshold_distance2);
            #endif

            if (d2 < 0.0) return -999;
            if (d2 < threshold_distance2) // --- ltr --> confirmed
            {
                last_count = count;
                count--;

                #ifdef DEBUG
                printf("--- ltr -->  CNT: %d\n", count);
                #endif

                // do // wait for person to leave measurement area
                // {
                //     d2 = getDistanceCM(TRIGGER2, ECHO2);
                //     if (d2 < 0.0) return -999;

                //     #ifdef DEBUG
                //     printf("leave D2: %.2f [%.2f]\n", d2, threshold_distance2);
                //     #endif
                // } while (d2 < threshold_distance2);

                delayMS(TTL);

                return count;
            }

            delayMS(DELAY);
        }

        return -999;
        
    }
    else if (d2 < threshold_distance2) // assuming <-- rtl ---
    {
        #ifdef DEBUG
        printf("D2 sensed, Waiting for D1\n");
        #endif

        for (size_t i = 0; i < SECONDSENSOR; i++) // wait ~2.5sec to confirm
        {
            d1 = getDistanceCM(TRIGGER1, ECHO1);

            #ifdef DEBUG
            printf("D1: %.2f [%.2f]\n", d1, threshold_distance1);
            #endif

            if (d1 < 0.0) return -999;
            if (d1 < threshold_distance1) // <-- rtl --- confirmed
            {
                last_count = count;
                count++;

                #ifdef DEBUG
                printf("<-- rtl ---  CNT: %d\n", count);
                #endif

                // do // wait for person to leave measurement area
                // {
                //     d1 = getDistanceCM(TRIGGER1, ECHO1);
                //     if (d1 < 0.0) return -999;

                //     #ifdef DEBUG
                //     printf("leave D1: %.2f [%.2f]\n", d1, threshold_distance1);
                //     #endif
                // } while (d1 < threshold_distance1);

                delayMS(TTL);

                return count;
            }

            delayMS(DELAY);
        }

        return -999;
        
    }
    else
    {
        last_count = count;
    }
    

    delayMS(DELAY);

    return count;
}
