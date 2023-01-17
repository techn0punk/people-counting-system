#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <time.h>
#include <sys/ioctl.h>
#include <sys/epoll.h>
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
    delayUS(microseconds);
    ret = ioctl(req.fd, GPIOHANDLE_SET_LINE_VALUES_IOCTL, &data);
    close(req.fd);
}

float getPulseUS(int pin) {
    struct gpioevent_request req;
    req.lineoffset = pin;
    req.handleflags = GPIOHANDLE_REQUEST_INPUT;
    req.eventflags = GPIOEVENT_REQUEST_BOTH_EDGES;
    strcpy(req.consumer_label, "HC-SR04 Echo");

    int fd = open("/dev/gpiochip0", O_RDONLY);
    int ret = ioctl(fd, GPIO_GET_LINEEVENT_IOCTL, &req);
    close(fd);

    static struct epoll_event ev;
    ev.events = EPOLLIN;
    ev.data.fd = req.fd;
    int epfd = epoll_create(1);
    int res = epoll_ctl(epfd, EPOLL_CTL_ADD, req.fd, &ev);

    long long unsigned start, end;
    int nfds;
    
    for (int i = 0; i < 2; i++)
    {
        nfds = epoll_wait(epfd, &ev, 1, 1000);
        if (nfds != 0)
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
    }

    close(req.fd);

    return (float) (end - start) / 1000; // microseconds
}

float getDistanceCM(int trigger, int echo) {
    putPulse(trigger, 10);
    return getPulseUS(echo) / 58;
}