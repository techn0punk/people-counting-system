PROG = pcs
CC = gcc
CFLAGS = -g
LDFLAGS = -g

SRCS = main.c rpi.c display.c ultrasonic.c button.c led.c
OBJS = $(SRCS:.c=.o)
LIBS =

all: $(PROG)

$(PROG): $(OBJS)
	$(CC) $(LDFLAGS) -o $(PROG) $(OBJS) $(LIBS)

clean:
	rm $(OBJS) $(PROG)

run: $(PROG)
	./$(PROG)

install: $(PROG)
	cp -vf $(PROG) /usr/local/bin/$(PROG)
	cp -vf pcs.service /lib/systemd/system/pcs.service
	chmod -v 644 /lib/systemd/system/pcs.service
	systemctl enable pcs

uninstall:
	systemctl disable pcs
	rm -vf /lib/systemd/system/pcs.service
	rm -vf /usr/local/bin/$(PROG)

# Dependencies
display.o: rpi.o
ultrasonic.o: rpi.o
button.o: rpi.o
led.o: rpi.o
