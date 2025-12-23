CC = gcc
CFLAGS = -Werror -Wall -std=c99 #Debug

EXECS = fork fork-wait fork-data fork-file catcount

all: $(EXECS)

fork.o: fork.c
	$(CC) $(CFLAGS) -c fork.c

fork-wait.o: fork-wait.c
	$(CC) $(CFLAGS) -c fork-wait.c

fork-data.o: fork-data.c
	$(CC) $(CFLAGS) -c fork-data.c

fork-file.o: fork-file.c
	$(CC) $(CFLAGS) -c fork-file.c

catcount.o: catcount.c
	$(CC) $(CFLAGS) -c catcount.c

.PHONY: clean

clean:
	/bin/rm -rf $(EXECS) fork.o fork-wait.o fork-data.o fork-file.o
