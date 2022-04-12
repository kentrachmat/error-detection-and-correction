CC=gcc
CFLAGS=-Wall -g
LIB=$(wildcard *.c)
OBJ=$(LIB:.c=.o)
LDFLAGS=-lm

all: $(OBJ)

%.o: %.c %.h
	$(CC) $(CFLAGS) -c $<
clean:
	rm -f $(OBJ)
cleanall: clean
	rm -rf doc/

.PHONY: clean cleanall all
