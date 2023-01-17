#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <linux/gpio.h>
#include <sys/epoll.h>

int main(int argc, char **argv) {
    if (argc < 2)
    {
        printf("Usage: %s <GPIO number>\n", argv[0]);
        return 1;
    }

    struct gpioevent_request req;
    req.lineoffset = atoi(argv[1]);
    req.handleflags = GPIOHANDLE_REQUEST_INPUT;
    req.eventflags = GPIOEVENT_REQUEST_BOTH_EDGES;
    strcpy(req.consumer_label, "Event Test");

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
        nfds = epoll_wait(epfd, &ev, 1, 20000);
        if (nfds != 0)
        {
            struct gpioevent_data edata;
            read(req.fd, &edata, sizeof(edata));

            if (edata.id == 1) // if rising edge
            {
                start = edata.timestamp;
                printf("RISING EDGE  [%llu]\n", start);
            }
            else
            {
                end = edata.timestamp;
                printf("FALLING EDGE [%llu]\n", end);
            }
        }
    }
    
    printf("PULSE DURATION: %llu ns\n", end - start);
    
    return 0;
}