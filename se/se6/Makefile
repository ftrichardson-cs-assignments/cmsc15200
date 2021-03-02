OBJECTS = 
CFLAGS = -g -Wall -O3 --std=c11
LDLIBS= -l criterion -lm
INCLUDES=./include
SOURCE= ./src
TESTS=./tests
BIN= ./bin
CC=clang

all: student_test_se6 test_se6

student_test_se6: $(SOURCE)/se6.c $(SOURCE)/student_test_se6.c
	$(CC) $(CFLAGS) $(SOURCE)/se6.c $(SOURCE)/student_test_se6.c -o $(BIN)/$@ -I $(INCLUDES) $(LDLIBS)

test_se6: $(TESTS)/test_se6.c $(SOURCE)/se6.c
	$(CC) $(CFLAGS) $(TESTS)/test_se6.c $(SOURCE)/se6.c  -o $(BIN)/$@ -I $(INCLUDES) $(LDLIBS)

gen_score: test_se6
	-bin/test_se6 --json > results.log 2> results.json
	python3 tests/grader.py

clean:
	rm -f $(BIN)/student_test_se6 $(BIN)/test_se6
	rm -rf $(BIN)/*.dSYM
	rm -rf *~ */*~
