CC = gcc
CFLAGS = -std=gnu99 -Wall -g #-DDEBUG

EXECS = dlisttest

all: $(EXECS)

dnode.o: dnode.c dnode.h
	$(CC) $(CFLAGS) -c dnode.c dnode.h 
dlist.o: dlist.h dlist.c dnode.o 
	$(CC) $(CFLAGS) -c dlist.c dlist.h dnode.o

dlisttest: dnode.o dlist.o dlisttest.c
	$(CC) $(CFLAGS) -o dlisttest dlisttest.c dlist.o dnode.o

.PHONY: clean
clean:
	/bin/rm -rf $(EXECS) dnode.o dlist.o

