OBJECTS = 
CFLAGS = -g -Wall -O3 --std=c11
LDLIBS= -l criterion -lm
INCLUDES=./include
SOURCE= ./src
TESTS=./tests
BIN= ./bin
CC=clang

all: student_test_se3 test_se3

student_test_se3: $(SOURCE)/se3.c $(SOURCE)/student_test_se3.c
	$(CC) $(CFLAGS) $(SOURCE)/se3.c $(SOURCE)/student_test_se3.c -o $(BIN)/$@ -I $(INCLUDES) $(LDLIBS)

test_se3: $(TESTS)/test_se3.c $(SOURCE)/se3.c
	$(CC) $(CFLAGS) $(TESTS)/test_se3.c $(SOURCE)/se3.c  -o $(BIN)/$@ -I $(INCLUDES) $(LDLIBS)

gen_score: test_se3
	-bin/test_se3 --json > results.log 2> results.json
	python3 tests/grader.py

clean:
	rm -f results.json results.log
	rm -f $(BIN)/student_test_se3 $(BIN)/test_se3
	rm -rf $(BIN)/*.dSYM
	rm -rf *~ */*~
