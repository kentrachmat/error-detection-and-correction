CC=gcc
CFLAGS=-Wall -g -I ../lib
TESTS_SRC=$(wildcard *.c)
TESTS_OBJ=$(TESTS_SRC:.c=.o)
TESTS_EXE=$(TESTS_SRC:.c=)
TP_SRC=$(wildcard ../lib/*.c)
TP_OBJ=$(TP_SRC:.c=.o)
LDFLAGS=-lm

all: $(TESTS_EXE)

$(TESTS_EXE): % : %.o $(TP_OBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)
%.o: %.c %.h
	$(CC) $(CFLAGS) -c $<
../%.o: ../%.c ../%.h
	make -C ..

clean:
	rm -f $(TESTS_OBJ) $(TESTS_EXE)
