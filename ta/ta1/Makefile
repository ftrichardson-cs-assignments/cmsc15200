OBJECTS = ta1 ta2 ta3
CFLAGS = -g -Wall -O3 --std=c11
LDLIBS= -l criterion -lm
INCLUDES=./include
SOURCE= ./src
TESTS=./tests
BIN= ./bin
CC=clang

all: ta1 ta2 ta3

ta1: ta1.c
	$(CC) $(CFLAGS) $? -o $@ $(LDLIBS)

ta2: ta2.c
	$(CC) $(CFLAGS) $? -o $@ $(LDLIBS)

ta3: ta3.c
	$(CC) $(CFLAGS) $? -o $@ $(LDLIBS)

clean:
	rm -f ${OBJECTS}
	rm -rf *.dSYM
	rm -f *~

