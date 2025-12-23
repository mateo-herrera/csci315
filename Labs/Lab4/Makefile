CC = gcc

CFLAGS = -std=gnu99 -Wall

EXECS = echod echoreq echoreq2

OBJS = wrappers.o echod.o echoreq.o echoreq2.o

all: $(EXECS)

wrappers.o: wrappers.c wrappers.h
	$(CC) $(CFLAGS) -c wrappers.c

echod: echod.o wrappers.o
	$(CC) $(CFLAGS) -o echod echod.o wrappers.o

echoreq: echoreq.o wrappers.o
	$(CC) $(CFLAGS) -o echoreq echoreq.o wrappers.o

echoreq2: echoreq2.o wrappers.o
	$(CC) $(CFLAGS) -o echoreq2 echoreq2.o wrappers.o

.PHONY: clean

clean:
	/bin/rm -rf $(EXECS) $(OBJS)
