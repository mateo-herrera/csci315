CC = gcc
CFLAGS = -Werror -Wall -std=gnu99 
READFLAGS = -lreadline

EXECS = heap-test pipe-test pipes upper tokens

all: $(EXECS)

heap-test.o: heap-test.c
	$(CC) $(CFLAGS) -c heap-test.c

pipe-test.o: pipe-test.c
	$(CC) $(CFLAGS) -c pipe-test.c

pipes.o: pipes.c
	$(CC) $(CFLAGS) -c pipes.c

upper.o: upper.c
	$(CC) $(CFLAGS) -c upper.c

tokens: tokens.c
	$(CC) $(CFLAGS) tokens.c -o tokens $(READFLAGS)

.PHONY: clean

clean:
	/bin/rm -rf $(EXECS) heap-test.o pipe-test.o pipes.o
