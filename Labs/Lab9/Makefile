
CC = gcc -I ./include
CFLAGS = -std=gnu -Wall -g

SRC = ./src
INC = ./include
BIN = ./bin
OBJ = ./obj

vpath %.h ./include
vpath %.c ./src

EXECS = ishell

all: mkpaths $(EXECS)

mkpaths:
	@ mkdir -p $(BIN)
	@ mkdir -p $(OBJ)

wrappers.o: wrappers.h wrappers.c
	@ mkdir -p $(OBJ)
	$(CC) $(CFLAGS) -c $(SRC)/wrappers.c -o $(OBJ)/wrappers.o

ishell: ishell.c wrappers.o
	@ mkdir -p $(BIN)
	$(CC) $(CFLAGS) $(OBJ)/wrappers.o $(SRC)/ishell.c -o $(BIN)/ishell

.PHONY: clean
clean:
	/bin/rm -rf $(BIN)/* $(OBJ)/* core* *~ $(SRC)/*~ $(INC)/*~
