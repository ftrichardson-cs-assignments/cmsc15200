CS 152, Winter 2021
README file for SE #2

Makefile: file to be used with make.  Run:
  make test_se2 - to compile your code and generate an executable for the automated test code
  make student_test_se2 - to compile your code and generate an executable for your tests
  make all - to do both
  make clean - remove generated files
  make gen_score - generate your score on the automated tests.

src: a subdirectory for the C source files
  se2.c - the C file for the short exercises.  You will do most of your work in this file.
  student_test_se2.c - a C file that you can use to test your code by hand.  Add calls
    to your functions to the main function.

include: a directory for the C header files
  se2.h - the include file for the short exercises.
  
bin: a subdirectory that will be used to hold the binary executables

tests - a directory that will hold the automated test files
  test_se2.c - the Criterion tests for the short exercises
  grader.py - a Python file used to compute short exercise scores.

README.txt: this file
