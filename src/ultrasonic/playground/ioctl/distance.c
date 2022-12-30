#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <sys/ioctl.h>
#include <linux/gpio.h>

#define TRIGGER 23
#define ECHO 24


/**
 * @brief Pauses the program for the amount of time (in microseconds)
 * specified by the parameter. There are a thousand microseconds in a
 * millisecond and a million microseconds in a second.
 * 
 * @param microseconds 
 */
void delayMicroseconds(long microseconds) {
    const clock_t clocks_per_us = (clock_t) (CLOCKS_PER_SEC / 1000000);
    const clock_t cycles_to_wait = (clock_t) (microseconds * clocks_per_us);
    clock_t start = clock();
    while (clock() < start + cycles_to_wait);
}

/**
 * @brief Puts a high Pulse on the given Pin for the given amount of time.
 * 
 * @param pin 
 * @param microseconds 
 */
void putPulse(int pin, long microseconds) {
    struct gpiohandle_request req;
    req.lineoffsets[0] = pin;
    req.flags = GPIOHANDLE_REQUEST_OUTPUT;
    req.default_values[0] = 0;
    strcpy(req.consumer_label, "HC-SR04 Trigger");
    req.lines = 1;

    int fd = open("/dev/gpiochip0", O_RDONLY);
    int ret = ioctl(fd, GPIO_GET_LINEHANDLE_IOCTL, &req);
    close(fd);

    struct gpiohandle_data data;
    data.values[0] = 1;
    ret = ioctl(req.fd, GPIOHANDLE_SET_LINE_VALUES_IOCTL, &data);
    data.values[0] = 0;
    delayMicroseconds(microseconds);
    ret = ioctl(req.fd, GPIOHANDLE_SET_LINE_VALUES_IOCTL, &data);
    close(req.fd);
}

int main(void) {

    while(1) {
        putPulse(23, 5);
        delayMicroseconds(10000);
    }

    return 0;
    
}