OBJECTS = 
CFLAGS = -g -Wall -O3 --std=c11
LDLIBS= -l criterion -lm
INCLUDES=./include
SOURCE= ./src
TESTS=./tests
BIN= ./bin
CC=clang

all: student_test_se4 test_se4

student_test_se4: $(SOURCE)/se4.c $(SOURCE)/student_test_se4.c
	$(CC) $(CFLAGS) $(SOURCE)/se4.c $(SOURCE)/student_test_se4.c -o $(BIN)/$@ -I $(INCLUDES) $(LDLIBS)

test_se4: $(TESTS)/test_se4.c $(SOURCE)/se4.c
	$(CC) $(CFLAGS) $(TESTS)/test_se4.c $(SOURCE)/se4.c  -o $(BIN)/$@ -I $(INCLUDES) $(LDLIBS)

gen_score: test_se4
	-bin/test_se4 --json > results.log 2> results.json
	python3 tests/grader.py

clean:
	rm -f results.json results.log
	rm -f $(BIN)/student_test_se4 $(BIN)/test_se4
	rm -rf $(BIN)/*.dSYM
	rm -rf *~ */*~
