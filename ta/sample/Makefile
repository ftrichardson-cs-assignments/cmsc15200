OBJECTS = ta1
CFLAGS = -g -Wall -O3 --std=c11
LDLIBS= -l criterion -lm
INCLUDES=./include
SOURCE= ./src
TESTS=./tests
BIN= ./bin
CC=clang

all: ta1

ta1: ta1.c
	$(CC) $(CFLAGS) $? -o $@ $(LDLIBS)

clean:
	rm -f ${OBJECTS}
	rm -rf *.dSYM
	rm -f *~

