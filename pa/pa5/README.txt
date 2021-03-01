CS 152, Winter 2021
README file for PA #3: Simulating multiple cores

Makefile: file to be used with make.  Run:
  make test_core_simulator - to compile your code and generate an executable for the automated test code
  make student_test_task - to compile your code and generate an executable for your
    task tests.
  make student_test_task_manager - to compile your code and generate an executable for your
    task manager tests.
  make student_test_scheduler - to compile your code and generate an executable for your
    scheduler tests.
  make all - to do all four
  make clean - remove generated files
  make gen_score - generate your score on the automated tests.

src: a subdirectory for the C source files
  task.c - the C file for Part 1
  task_manager.c - the C file for Part 2.
  scheduler.c - the C file for Part 3.
  student_test_task.c - a C file that you can use to test your task API code by hand.  Add calls
    to your functions to the main function.  Add test helper functions as needed.
  student_test_task_manager.c - a C file that you can use to test your task manager API code by hand.  Add calls
    to your functions to the main function.  Add test helper functions as needed.
  student_test_schedule.c - a C file that you can use to test your scheduler by hand.  Add calls
    to your functions to the main function.  Add test helper functions as needed.

include: a directory for the C header files
  task.h - the include file for the task API
  task_manager.h - the include file for the task manager API
  scheduler.h - the include file for the scheduler
  util.h - the include file for our test utility functions (you will not use these functions)
  test_helpers.h - the include file for more of our test utility functions (you will not use these functions)
  
bin: a subdirectory that will be used to hold the binary executables

tests: a directory for the automated test files
  test_task_manager.c - the Criterion tests for the programming assignment
  grader.py - a Python file used to compute the Completeness score.
  util.c - helper functions used by the test code.
  test_helpers.c - more helper functions used by the test code.  

README.txt: this file
