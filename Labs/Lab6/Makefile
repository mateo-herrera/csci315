CC = gcc

CFLAGS = -std=gnu99 -Wall
PTHREADFLAGS = -lpthread


EXECS = dp problem1 problem2 problem3-1 problem3-2

all: $(EXECS)

dp: dp.c
	$(CC) $(CFLAGS) dp.c -o dp $(PTHREADFLAGS)

problem1: problem1.c
	$(CC) $(CFLAGS) problem1.c -o problem1 $(PTHREADFLAGS)

problem2: problem2.c
	$(CC) $(CFLAGS) problem2.c -o problem2 $(PTHREADFLAGS)

problem3-1: problem3-1.c
	$(CC) $(CFLAGS) problem3-1.c -o problem3-1 $(PTHREADFLAGS)

problem3-2:	problem3-2.c
	$(CC) $(CFLAGS) problem3-2.c -o problem3-2 $(PTHREADFLAGS)

.PHONY: clean

clean:
	/bin/rm -rf $(EXECS)
