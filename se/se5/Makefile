OBJECTS = 
CFLAGS = -g -Wall -O3 --std=c11
LDLIBS= -l criterion -lm
INCLUDES=./include
SOURCE= ./src
TESTS=./tests
BIN= ./bin
CC=clang

all: student_test_se5 test_se5

student_test_se5: $(SOURCE)/se5.c $(SOURCE)/student_test_se5.c
	$(CC) $(CFLAGS) $(SOURCE)/se5.c $(SOURCE)/student_test_se5.c -o $(BIN)/$@ -I $(INCLUDES) $(LDLIBS)

test_se5: $(TESTS)/test_se5.c $(SOURCE)/se5.c
	$(CC) $(CFLAGS) $(TESTS)/test_se5.c $(SOURCE)/se5.c  -o $(BIN)/$@ -I $(INCLUDES) $(LDLIBS)

clean:
	rm -f $(BIN)/student_test_se5 $(BIN)/test_se5
	rm -rf $(BIN)/*.dSYM
	rm -rf *~ */*~
