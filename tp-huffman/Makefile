TP=huffman
CC=gcc
MAKE=make
CFLAGS=-Wall -g
LIB=$(wildcard lib/*.c)
OBJ=$(LIB:.c=.o)
LDFLAGS=-lm
ARCHIVE_FILES=$(wildcard *.c lib/*.c lib/*.h tests/*.h tests/*.c) lib/Makefile tests/Makefile Makefile AUTHORS
MAIN=main huffman
MAIN_OBJ=$(MAIN:=.o)

all: library $(MAIN)

$(MAIN): % : %.o $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)
%.o: %.c %.h
	$(CC) $(CFLAGS) -c $<
library: 
	$(MAKE) -C lib
clean:
	rm -f $(OBJ) $(MAIN) $(MAIN_OBJ)
cleanall: clean
	rm -rf doc/
doc: $(SRC)
	doxygen .doxyfile
archive: tp-$(TP).zip
tp-$(TP).zip: $(ARCHIVE_FILES)
	zip $@ $(ARCHIVE_FILES)

.PHONY: clean archive all
