#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <linux/gpio.h>

int main(int argc, char **argv) {
    if (argc < 3)
    {
        printf("Usage: %s <GPIO number> <value 0/1>\n", argv[0]);
        return 1;
    }

    struct gpiohandle_request req;
    req.lineoffsets[0] = atoi(argv[1]);
    req.flags = GPIOHANDLE_REQUEST_OUTPUT;
    req.default_values[0] = 0;
    strcpy(req.consumer_label, "Output test");
    req.lines = 1;

    int fd = open("/dev/gpiochip0", O_RDONLY);
    int ret = ioctl(fd, GPIO_GET_LINEHANDLE_IOCTL, &req);
    close(fd);

    struct gpiohandle_data data;
    data.values[0] = atoi(argv[2]);
    ret = ioctl(req.fd, GPIOHANDLE_SET_LINE_VALUES_IOCTL, &data);
    close(req.fd);

    return 0;
}