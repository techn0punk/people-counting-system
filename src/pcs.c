#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <sys/ioctl.h>
#include <linux/gpio.h>

void delayUS(long microseconds) {
    const clock_t clocks_per_us = (clock_t) (CLOCKS_PER_SEC / 1000000);
    const clock_t cycles_to_wait = (clock_t) (microseconds * clocks_per_us);
    clock_t start = clock();
    while (clock() < start + cycles_to_wait);
}

void delayMS(long milliseconds) {
    const clock_t clocks_per_ms = (clock_t) (CLOCKS_PER_SEC / 1000);
    const clock_t cycles_to_wait = (clock_t) (milliseconds * clocks_per_ms);
    clock_t start = clock();
    while (clock() < start + cycles_to_wait);
}

void digitalWrite(int pin, int value) {
    struct gpiohandle_request req;
    req.lineoffsets[0] = pin;
    req.flags = GPIOHANDLE_REQUEST_OUTPUT;
    req.default_values[0] = 0;
    strcpy(req.consumer_label, "Digital output");
    req.lines = 1;

    int fd = open("/dev/gpiochip0", O_RDONLY);
    int ret = ioctl(fd, GPIO_GET_LINEHANDLE_IOCTL, &req);
    close(fd);

    struct gpiohandle_data data;
    data.values[0] = value;
    ret = ioctl(req.fd, GPIOHANDLE_SET_LINE_VALUES_IOCTL, &data);
    close(req.fd);
}

int digitalRead(int pin) {
    struct gpiohandle_request req;
    req.lineoffsets[0] = pin;
    req.flags = GPIOHANDLE_REQUEST_INPUT;
    strcpy(req.consumer_label, "Digital input");
    req.lines = 1;

    int fd = open("/dev/gpiochip0", O_RDONLY);
    int ret = ioctl(fd, GPIO_GET_LINEHANDLE_IOCTL, &req);
    close(fd);

    struct gpiohandle_data data;
    ret = ioctl(req.fd, GPIOHANDLE_GET_LINE_VALUES_IOCTL, &data);
    close(req.fd);

    return data.values[0];
}