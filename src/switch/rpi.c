#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <sys/ioctl.h>
#include <sys/epoll.h>
#include <linux/gpio.h>
#include "rpi.h"

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

int digitalWrite(int pin, int value) {
    struct gpiohandle_request req;
    req.lineoffsets[0] = pin;
    req.flags = GPIOHANDLE_REQUEST_OUTPUT;
    req.default_values[0] = 0;
    strcpy(req.consumer_label, "Digital output");
    req.lines = 1;

    int fd = open("/dev/gpiochip0", O_RDONLY);
    if (fd == -1) return fd;

    int ret = ioctl(fd, GPIO_GET_LINEHANDLE_IOCTL, &req);
    close(fd);
    if (ret == -1) return ret;

    struct gpiohandle_data data;
    data.values[0] = value;
    ret = ioctl(req.fd, GPIOHANDLE_SET_LINE_VALUES_IOCTL, &data);
    close(req.fd);
    if (ret == -1) return ret;
}

int digitalRead(int pin) {
    struct gpiohandle_request req;
    req.lineoffsets[0] = pin;
    req.flags = GPIOHANDLE_REQUEST_INPUT;
    strcpy(req.consumer_label, "Digital input");
    req.lines = 1;

    int fd = open("/dev/gpiochip0", O_RDONLY);
    if (fd == -1) return fd;

    int ret = ioctl(fd, GPIO_GET_LINEHANDLE_IOCTL, &req);
    close(fd);
    if (ret == -1) return ret;

    struct gpiohandle_data data;
    ret = ioctl(req.fd, GPIOHANDLE_GET_LINE_VALUES_IOCTL, &data);
    close(req.fd);
    if (ret == -1) return ret;

    return data.values[0];
}

int putPulse(int pin, long microseconds) {
    struct gpiohandle_request req;
    req.lineoffsets[0] = pin;
    req.flags = GPIOHANDLE_REQUEST_OUTPUT;
    req.default_values[0] = 0;
    strcpy(req.consumer_label, "HC-SR04 Trigger");
    req.lines = 1;

    int fd = open("/dev/gpiochip0", O_RDONLY);
    if (fd == -1) return fd;

    int ret = ioctl(fd, GPIO_GET_LINEHANDLE_IOCTL, &req);
    close(fd);
    if (ret == -1) return ret;

    struct gpiohandle_data data;
    data.values[0] = 1;
    ret = ioctl(req.fd, GPIOHANDLE_SET_LINE_VALUES_IOCTL, &data);
    if (ret == -1) {
        close(req.fd);
        return ret;
    }

    data.values[0] = 0;
    delayUS(microseconds);
    ret = ioctl(req.fd, GPIOHANDLE_SET_LINE_VALUES_IOCTL, &data);
    close(req.fd);
    if (ret == -1) return ret;

    return 0;
}

float getPulseUS(int pin) {
    struct gpioevent_request req;
    req.lineoffset = pin;
    req.handleflags = GPIOHANDLE_REQUEST_INPUT;
    req.eventflags = GPIOEVENT_REQUEST_BOTH_EDGES;
    strcpy(req.consumer_label, "HC-SR04 Echo");

    int fd = open("/dev/gpiochip0", O_RDONLY);
    if (fd == -1) return -1.0f;

    int ret = ioctl(fd, GPIO_GET_LINEEVENT_IOCTL, &req);
    close(fd);
    if (ret == -1) return -1.0f;

    static struct epoll_event ev;
    ev.events = EPOLLIN;
    ev.data.fd = req.fd;
    int epfd = epoll_create(1);
    if (epfd == -1) {
        close(req.fd);
        return -1.0f;
    }

    int res = epoll_ctl(epfd, EPOLL_CTL_ADD, req.fd, &ev);
    if (res == -1) {
        close(req.fd);
        close(epfd);
        return -1.0f;
    }
    

    long long unsigned start, end;
    int nfds;
    
    for (int i = 0; i < 2; i++)
    {
        nfds = epoll_wait(epfd, &ev, 1, 1000);
        if (nfds > 0)
        {
            struct gpioevent_data edata;
            read(req.fd, &edata, sizeof(edata));

            if (edata.id == 1) // if rising edge
            {
                start = edata.timestamp; // nanoseconds
            }
            else
            {
                end = edata.timestamp; // nanoseconds
            }
        }
        else
        {
            close(req.fd);
            close(epfd);
            return -1.0f;
        }
        
    }

    close(epfd);
    close(req.fd);

    return (float) (end - start) / 1000; // microseconds
}