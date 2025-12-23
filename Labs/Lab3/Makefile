CC = gcc
CFLAGS = -std=gnu99 -Wall
PTHREADFLAGS = -lpthread
MATHFLAGS = -lm

EXECS = summation mytime char-threads summation3 summation4

all: $(EXECS)

summation: summation.c
	$(CC) $(CFLAGS) summation.c -o summation $(PTHREADFLAGS) $(MATHFLAGS)

summation3: summation3.c
	$(CC) $(CFLAGS) summation3.c -o summation3 $(PTHREADFLAGS) $(MATHFLAGS)

summation4: summation4.c
	$(CC) $(CFLAGS) summation4.c -o summation4 $(PTHREADFLAGS) $(MATHFLAGS)

char-threads: char-threads.c
	$(CC) $(CFLAGS) char-threads.c -o char-threads $(PTHREADFLAGS)

mytime: mytime.c
	$(CC) $(CFLAGS) mytime.c -o mytime

.PHONY: clean

clean:
	/bin/rm -rf $(EXECS)
