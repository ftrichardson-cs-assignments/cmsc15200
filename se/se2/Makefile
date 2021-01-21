OBJECTS = 
CFLAGS = -g -Wall -O3 --std=c11
LDLIBS= -l criterion -lm
INCLUDES=./include
SOURCE= ./src
TESTS=./tests
BIN= ./bin
CC=clang

all: student_test_se2 test_se2

student_test_se2: $(SOURCE)/se2.c $(SOURCE)/student_test_se2.c
	$(CC) $(CFLAGS) $(SOURCE)/se2.c $(SOURCE)/student_test_se2.c -o $(BIN)/$@ -I $(INCLUDES) $(LDLIBS)

test_se2: $(TESTS)/test_se2.c $(SOURCE)/se2.c
	$(CC) $(CFLAGS) $(TESTS)/test_se2.c $(SOURCE)/se2.c  -o $(BIN)/$@ -I $(INCLUDES) $(LDLIBS)

gen_score: test_se2
	-bin/test_se2 --json > results.log 2> results.json
	python3 tests/grader.py

clean:
	rm -f results.json results.log
	rm -f $(BIN)/student_test_se2 $(BIN)/test_se2
	rm -rf $(BIN)/*.dSYM
	rm -rf *~ */*~
