PROG = pcs
CC = gcc
CFLAGS = -g -DDEBUG
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

# Dependencies
display.o: rpi.o
ultrasonic.o: rpi.o
button.o: rpi.o
led.o: rpi.o
