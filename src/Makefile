PROG = pcs
CC = gcc
CFLAGS = -g
LDFLAGS = -g

SRCS = main.c pcs.c
OBJS = $(SRCS:.c=.o)
LIBS =

all: $(PROG)

$(PROG): $(OBJS)
	$(CC) $(LDFLAGS) -o $(PROG) $(OBJS) $(LIBS)

clean:
	rm $(OBJS) $(PROG)