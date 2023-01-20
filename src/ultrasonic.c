#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <time.h>
#include <sys/ioctl.h>
#include <sys/epoll.h>
#include <linux/gpio.h>
#include "rpi.h"
#include "ultrasonic.h"

int count;

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

    return 0;
}

int updateCount(void) {

    return 0;
}