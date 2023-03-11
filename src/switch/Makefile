PROG = button
CC = gcc
CFLAGS = -g -DDEBUG
LDFLAGS = -g

SRCS = rpi.c button.c
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
button.o: rpi.o