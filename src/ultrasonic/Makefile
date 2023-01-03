PROG = direction
CC = gcc
CFLAGS = -g
LDFLAGS = -g

SRCS = direction.c distance.c
OBJS = $(SRCS:.c=.o)
LIBS =

all: $(PROG)

$(PROG): $(OBJS)
	$(CC) $(LDFLAGS) -o $(PROG) $(OBJS) $(LIBS)

clean:
	rm $(OBJS)

realclean: clean
	rm $(PROG)