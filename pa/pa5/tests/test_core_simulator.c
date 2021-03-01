/* CMSC 15200, Winter 2021
 *  PA #5 Task Manager: automated test code
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <criterion/criterion.h>

#include "task.h"
#include "task_manager.h"
#include "scheduler.h"
#include "util.h"
#include "test_helpers.h"

/* Replicate the hidden types here to allow the test code
 * to check the implementation.
 */
 
/* Replicate the hidden types here to allow the test code
 * to check the implementation.
 */
 
struct task {
    int tid;      // task identifier
    int priority; // task priority
    int run_time; // task run-time.
};

#define INITIAL_HEAP_SIZE 5
#define GROWTH_MULTIPLIER 2

/* Structure definition for the task manager */
struct task_manager {
  int next_heap_slot;
  int heap_size;
  task_t **heap;
};

void verify_task(task_t *task, task_t expected_task,
		 char *test_desc, char *test_str);

void verify_tm(task_manager_t *tm, int num_tasks, int heap_size, int task_order[],
	       task_t tasks[], char *test_desc, char *test_str);

void verify_empty_tm(task_manager_t *tm, int expected_heap_size,
		     char *test_desc, char *test_str);
task_manager_t *mk_sample_tm(int num_tasks, int expected_heap_size, int task_order[],
			     task_t tasks[], char *test_desc, char *test_str);

task_manager_t *mk_zero(char *test_str);

task_manager_t *mk_one(char *test_str);


/***************************************************************/
TestSuite(tm_add_task, .timeout=60);

Test(tm_add_task, testA) 
{
    task_manager_t *tm = mk_zero("tm_add_task/testA");
    tm_free(tm);
}

Test(tm_add_task, testB) 
{
    task_manager_t *tm = mk_one("tm_add_task/testB");
    tm_free(tm);
}

Test(tm_add_task, testC)
{
    int num_tasks = 2;
    task_t tasks[] = {{0, 2, 20}, {1, 0, 10}};
    int task_order[] = {0, 1};
    char *test_desc = "Add task: add two tasks to an empty Task Manager in order of priority";
    char *test_str = "tm_add_task/testC";

    task_manager_t *tm = mk_sample_tm(num_tasks, INITIAL_HEAP_SIZE, task_order,
				      tasks, test_desc, test_str);
    tm_free(tm);                                      
}

Test(tm_add_task, testD)
{
    int num_tasks = 2;
    task_t tasks[] = {{0, 0, 20}, {1, 2, 10}};
    int task_order[] = {1, 0};
    char *test_desc = "Add task: add two tasks to an empty Task Manager in reverse order of priority";
    char *test_str = "tm_add_task/testD";

    task_manager_t *tm = mk_sample_tm(num_tasks, INITIAL_HEAP_SIZE, task_order,
				      tasks, test_desc, test_str);
    tm_free(tm);                                      
}

Test(tm_add_task, testE)
{
    int num_tasks = 2;
    task_t tasks[] = {{0, 0, 10}, {1, 0, 20}};
    int task_order[] = {0, 1};
    char *test_desc = "Add task: add two tasks to an empty Task Manager with equal priorities and different runtimes";
    char *test_str = "tm_add_task/testE";

    task_manager_t *tm = mk_sample_tm(num_tasks, INITIAL_HEAP_SIZE, task_order,
				      tasks, test_desc, test_str);
    tm_free(tm);                                      
}

Test(tm_add_task, testF)
{
    int num_tasks = 2;
    task_t tasks[] = {{0, 0, 20}, {1, 0, 10}};
    int task_order[] = {1, 0};
    char *test_desc = "Add task: add two tasks to an empty Task Manager with equal priorities and different runtimes";
    char *test_str = "tm_add_task/testF";

    task_manager_t *tm = mk_sample_tm(num_tasks, INITIAL_HEAP_SIZE, task_order,
				      tasks, test_desc, test_str);
    tm_free(tm);                                      
}

Test(tm_add_task, testG)
{
    int num_tasks = 2;
    task_t tasks[] = {{0, 2, 20}, {1, 2, 20}};
    int task_order[] = {0, 1};
    char *test_desc = "Add task: add two tasks with the same urgency to an empty Task Manager";
    char *test_str = "tm_add_task/testG";

    task_manager_t *tm = mk_sample_tm(num_tasks, INITIAL_HEAP_SIZE, task_order,
				      tasks, test_desc, test_str);
    tm_free(tm);                                      
}

Test(tm_add_task, testH)
{
    int num_tasks = 7;
    task_t tasks[] = {{0, 10, 5}, {1, 8, 10}, {2, 8, 5}, {3, 7, 10}, {4, 7, 10}, {5, 6, 5}, {6, 5, 3}};
    int task_order[] = {0, 1, 2, 3, 4, 5, 6};
    char *test_desc = "Add task: add seven tasks in heap order.  No sifting needed.  Heap array will grow";
    char *test_str = "tm_add_task/testH";

    task_manager_t *tm = mk_sample_tm(num_tasks, INITIAL_HEAP_SIZE*GROWTH_MULTIPLIER, task_order,
				      tasks, test_desc, test_str);
    tm_free(tm);                                      
}



Test(tm_add_task, testI)
{
    int num_tasks = 8;
    task_t tasks[] = {{0, 10, 5}, {1, 8, 10}, {2, 8, 5}, {3, 7, 10}, {4, 7, 10}, 
		      {5, 6, 5}, {6, 5, 3}, {7, 9, 10}};
    int task_order[] = {0, 7, 2, 1, 4, 5, 6, 3};
    char *test_desc = "Add task: add seven tasks in heap order. Sift up part-way.";
    char *test_str = "tm_add_task/testI";

    int heap_size = INITIAL_HEAP_SIZE*GROWTH_MULTIPLIER;
    task_manager_t *tm = mk_sample_tm(num_tasks, heap_size,
				      task_order, tasks,
                                      test_desc, test_str);
    tm_free(tm);
}

Test(tm_add_task, testJ)
{
    int num_tasks = 9;
    task_t tasks[] = {{0, 10, 5}, {1, 8, 10}, {2, 8, 5}, {3, 7, 10}, {4, 7, 10}, 
		      {5, 6, 5}, {6, 5, 3}, {7, 9, 10}, {8, 12, 10}};
    int task_order[] = {8, 0, 2, 7, 4, 5, 6, 3, 1};
    char *test_desc = "Add task: add nine tasks in heap order. Sift up to root.";
    char *test_str = "tm_add_task/testJ";

    int heap_size = INITIAL_HEAP_SIZE*GROWTH_MULTIPLIER;
    task_manager_t *tm = mk_sample_tm(num_tasks, heap_size,
				      task_order, tasks,
                                      test_desc, test_str);
    tm_free(tm);
}

Test(tm_add_task, testK)
{
    int num_tasks = 11;
    task_t tasks[] = {{0, 10, 5}, {1, 8, 10}, {2, 8, 5}, {3, 7, 10}, {4, 7, 10}, 
		      {5, 6, 5}, {6, 5, 3}, {7, 9, 10}, {8, 12, 10}, {9, 1, 4}, {10, 1, 5}};
    int task_order[] = {8, 0, 2, 7, 4, 5, 6, 3, 1, 9, 10};
    char *test_desc = "Add: add 11 tasks (grow the heap twice)";
    char *test_str = "tm_add_task/testK";

    int heap_size = INITIAL_HEAP_SIZE*GROWTH_MULTIPLIER*GROWTH_MULTIPLIER;

    task_manager_t *tm = mk_sample_tm(num_tasks, heap_size,
				      task_order, tasks,
                                      test_desc, test_str);
    tm_free(tm);
}



/***************************************************************/
TestSuite(tm_is_empty, .timeout=60);


Test(tm_is_empty, testA) 
{
    char *test_desc = "Checking empty TM";
    char *test_str = "tm_is_empty/testA";
    task_manager_t *tm = mk_zero(test_str);

    bool actual = tm_is_empty(tm);
    check_bool(actual, true, "result", test_desc, test_str);
}

Test(tm_is_empty, testB) 
{
    char *test_desc = "Checking TM w/ one task";
    char *test_str = "tm_is_empty/testB";
    task_manager_t *tm = mk_one(test_str);

    bool actual = tm_is_empty(tm);
    check_bool(actual, false, "result", test_desc, test_str);
}

Test(tm_is_empty, testC) 
{
    char *test_desc = "Checking TM w/ many tasks";
    char *test_str = "tm_is_empty/testC";
    int num_tasks = 9;
    task_t tasks[] = {{0, 10, 5}, {1, 8, 10}, {2, 8, 5}, {3, 7, 10}, {4, 7, 10}, 
		      {5, 6, 5}, {6, 5, 3}, {7, 9, 10}, {8, 12, 10}};
    int task_heap_order[] = {8, 0, 2, 7, 4, 5, 6, 3, 1};
    int expected_heap_size = INITIAL_HEAP_SIZE * GROWTH_MULTIPLIER;

    task_manager_t *tm = mk_sample_tm(num_tasks, expected_heap_size, task_heap_order,
				      tasks, test_desc,  test_str);
    bool actual = tm_is_empty(tm);
    check_bool(actual, false, "result", test_desc, test_str);
}




/***************************************************************/
TestSuite(tm_remove_most_urgent_task, .timeout=60);

void remove_helper(int num_tasks, int expected_heap_size, int task_heap_order[],
		   task_t tasks[], int task_remove_order[],
		   char *test_desc, char *test_str)
{
    task_manager_t *tm = mk_sample_tm(num_tasks, expected_heap_size, task_heap_order,
				      tasks, test_desc,  test_str);

    for (int i=0; i < num_tasks; i++) {
      task_t *actual = tm_remove_most_urgent_task(tm);
      int ti = task_remove_order[i];
      verify_task(actual, tasks[ti], test_desc, test_str);
      // done with the task.
      free(actual);
    }

    verify_empty_tm(tm, expected_heap_size, test_desc, test_str);
    tm_free(tm);
}

Test(tm_remove_most_urgent_task, testA) 
{
    char *test_desc = "Extracting the most urgent task from an empty task manager\n";
    char *test_str = "tm_remove_most_urgent_task/testA";
    task_manager_t *tm = mk_zero(test_str);

    task_t *actual = tm_remove_most_urgent_task(tm);

    cr_assert_eq(actual, NULL,
		 "Expected NULL from extracting the most urgent task from an empty task manager\n");

    verify_empty_tm(tm, INITIAL_HEAP_SIZE, test_desc, test_str);
}

Test(tm_remove_most_urgent_task, testB) 
{
    char *test_desc = "Remove one task from a task manager with one task.";
    char *test_str = "tm_remove_most_urgent_task/testB";

    task_t tasks[] = {{0, 2, 10}};
    int task_order[] = {0};

    remove_helper(1, INITIAL_HEAP_SIZE, task_order,
		  tasks, task_order,
		  test_desc, test_str);
}

Test(tm_remove_most_urgent_task, testC) 
{
    int num_tasks = 2;
    task_t tasks[] = {{0, 2, 20}, {1, 0, 10}};
    int task_order[] = {0, 1};

    char *test_desc = "Add/remove two tasks";
    char *test_str = "tm_remove_most_urgent_task/testC";

    remove_helper(num_tasks, INITIAL_HEAP_SIZE, task_order,
		  tasks, task_order,
		  test_desc, test_str);

}

Test(tm_remove_most_urgent_task, testD) 
{
    int num_tasks = 2;
    task_t tasks[] = {{0, 0, 20}, {1, 2, 10}};
    // correct is: 1, 0
    int task_order[] = {1, 0};
    int remove_order[] = {1, 0};

    char *test_desc = "Add/remove two tasks";
    char *test_str = "tm_remove_most_urgent_task/testD";

    remove_helper(num_tasks, INITIAL_HEAP_SIZE, task_order,
		  tasks, remove_order,
		  test_desc, test_str);
}

Test(tm_remove_most_urgent_task, testE)
{
    int num_tasks = 9;
    task_t tasks[] = {{0, 10, 5}, {1, 8, 10}, {2, 8, 5}, {3, 7, 10}, {4, 7, 10}, 
		      {5, 6, 5}, {6, 5, 3}, {7, 9, 10}, {8, 12, 10}};
    int task_order[] = {8, 0, 2, 7, 4, 5, 6, 3, 1};
    int remove_order[] = {8, 0, 7, 2, 1, 4, 3, 5, 6};
    char *test_desc = "Add task: add nine tasks in heap order. Sift up to root.";
    char *test_str = "tm_remove_most_urgent_task/testE";

    int heap_size = INITIAL_HEAP_SIZE*GROWTH_MULTIPLIER;

    remove_helper(num_tasks, heap_size, task_order,
		  tasks, remove_order,
		  test_desc, test_str);
}

Test(tm_remove_most_urgent_task, testF)
{
    int num_tasks = 11;
    task_t tasks[] = {{0, 10, 5}, {1, 8, 10}, {2, 8, 5}, {3, 7, 10}, {4, 7, 10}, 
		      {5, 6, 5}, {6, 5, 3}, {7, 9, 10}, {8, 12, 10}, {9, 1, 4}, {10, 1, 5}};
    int task_order[] = {8, 0, 2, 7, 4, 5, 6, 3, 1, 9, 10};
    int remove_order[] = {8, 0, 7, 2, 1, 3, 4, 5, 6, 9, 10};
    char *test_desc = "Remove tasks: add 11 tasks and then remove them";
    char *test_str = "tm_remove_most_urgent_task/testF";

    int heap_size = INITIAL_HEAP_SIZE*GROWTH_MULTIPLIER*GROWTH_MULTIPLIER;

    remove_helper(num_tasks, heap_size, task_order,
		  tasks, remove_order,
		  test_desc, test_str);
}


/***************************************************************/
TestSuite(tm_mixed, .timeout=60);

Test(tm_mixed, testA)
{
    int num_tasks = 4;
    task_t tasks[] = {{0, 1, 20}, {1, 2, 10}, {2, 2, 10}, {3, 2, 5}};
    int task_order[] = {3, 1, 2, 0};
    int time_slice = 6;
    char *test_desc = "Mix adds and removes";
    char *test_str = "tm_mixed/testA";    

    task_manager_t *tm = mk_sample_tm(num_tasks, INITIAL_HEAP_SIZE, task_order,
				      tasks, test_desc, test_str);

    task_t *core0 = tm_remove_most_urgent_task(tm);
    verify_task(core0, tasks[3], test_desc, test_str);

    task_t *core1 = tm_remove_most_urgent_task(tm);
    verify_task(core1, tasks[1], test_desc, test_str);    

    core0 = tm_remove_most_urgent_task(tm);
    verify_task(core0, tasks[2], test_desc, test_str);    

    core1 = tm_remove_most_urgent_task(tm);
    verify_task(core1, tasks[0], test_desc, test_str);

    task_t *t = mk_task(tasks[0].tid, tasks[0].priority, tasks[0].run_time - time_slice);
    tm_add_task(tm, t);

    core1 = tm_remove_most_urgent_task(tm);
    verify_task(core1, *t, test_desc, test_str);

    core1 = tm_remove_most_urgent_task(tm);
    cr_assert_eq(core1, NULL, "Expected NULL task from tm_remove_most_urgent_task");
    
    tm_free(tm);
}

Test(tm_mixed, testB)
{
    int num_tasks = 11;
    task_t tasks[] = {{0, 10, 5}, {1, 8, 10}, {2, 8, 5}, {3, 7, 10}, {4, 7, 10}, 
		      {5, 6, 5}, {6, 5, 3}, {7, 9, 10}, {8, 12, 10}, {9, 1, 4}, {10, 1, 5}};
    int task_order[] = {8, 0, 2, 7, 4, 5, 6, 3, 1, 9, 10};
    char *test_desc = "Add/Remove tasks from 11 task heap";
    char *test_str = "tm_mixed/testB";

    int heap_size = INITIAL_HEAP_SIZE*GROWTH_MULTIPLIER*GROWTH_MULTIPLIER;

    task_manager_t *tm = mk_sample_tm(num_tasks, heap_size, task_order,
				      tasks, test_desc, test_str);

    
    task_t *removed0 = tm_remove_most_urgent_task(tm);
    verify_task(removed0, tasks[8], test_desc, test_str);

    task_t *removed1 = tm_remove_most_urgent_task(tm);
    verify_task(removed1, tasks[0], test_desc, test_str);    

    task_t *removed2 = tm_remove_most_urgent_task(tm);
    verify_task(removed2, tasks[7], test_desc, test_str);    

    removed0->run_time -= 5;
    tm_add_task(tm, removed0);
    
    task_t *t = mk_task(11, 0, 10);
    tm_add_task(tm, t);
    
    task_t *removed3 = tm_remove_most_urgent_task(tm);
    verify_task(removed3, *removed0, test_desc, test_str);

    tm_free(tm);

}


/***************************************************************/

TestSuite(simulate_cores, .timeout=60);
void helper(int num_tasks, int expected_heap_size, int task_heap_order[],
	    task_t tasks[], int num_cores, int time_slice, int expected_num_cycles,
	    char *test_desc, char *test_str)
{
  task_manager_t *tm = mk_sample_tm(num_tasks, expected_heap_size, task_heap_order,
				    tasks, test_desc,  test_str);

  int expected_time = 0;
  for (int i = 0; i < num_tasks; i++) {
    expected_time += tasks[i].run_time;
  }
  
  // set to something other than zero to turn up uninitialized
  // value in the student's code.
  int total_time = 9999999;
  int nc = simulate_cores(tm, num_cores, time_slice, &total_time);

  check_int(nc, expected_num_cycles, "number of cycles", test_desc, test_str);
  check_int(total_time, expected_time, "total time", test_desc, test_str);  

  tm_free(tm);

}


Test(simulate_cores, testA) 
{
  int num_cores = 2;
  int time_slice = 10;
  // set to something other than zero to turn up uninitialized
  // value in the student's code.
  int total_time = 999999999;
  char *test_desc = "Empty task manager w/ twp cores";
  char *test_str = "simulate_cores/testA";

  task_manager_t *tm = mk_zero(test_str);

  int nc = simulate_cores(tm, num_cores, time_slice, &total_time);
  check_int(nc, 0, "number of cycles", test_desc, test_str);
  check_int(total_time, 0, "total time", test_desc, test_str);  

  tm_free(tm);
}


Test(simulate_cores, testB) 
{
  int num_tasks = 1;
  task_t tasks[] = {{0, 2, 10}};
  int task_order[] = {0};
  int num_cores = 1;
  int time_slice = 10;
  char *test_desc = "One task w/ one core, one cycle";
  char *test_str = "simulate_cores/testB";
  
  helper(num_tasks, INITIAL_HEAP_SIZE, task_order,
	 tasks, num_cores, time_slice, 1, test_desc, test_str);
 }

Test(simulate_cores, testC) 
{
  int num_tasks = 1;
  task_t tasks[] = {{0, 2, 10}};
  int task_order[] = {0};
  int num_cores = 1;
  int time_slice = 4;
  char *test_desc = "One task w/ one core, three cycles";
  char *test_str = "simulate_cores/testC";

  helper(num_tasks, INITIAL_HEAP_SIZE, task_order,
	 tasks, num_cores, time_slice, 3, test_desc, test_str);
}

Test(simulate_cores, testD) 
{
  int num_tasks = 2;
  task_t tasks[] = {{0, 2, 5}, {1, 2, 5}};
  int task_order[] = {0, 1};
  int num_cores = 1;
  int time_slice = 5;
  char *test_desc = "two tasks w/ one core, two cycles";
  char *test_str = "simulate_cores/testD";

  helper(num_tasks, INITIAL_HEAP_SIZE, task_order,
	 tasks, num_cores, time_slice, 2, test_desc, test_str);
}


Test(simulate_cores, testE) 
{
  int num_tasks = 2;
  task_t tasks[] = {{0, 2, 10}, {1, 2, 5}};
  int task_order[] = {1, 0};
  int num_cores = 1;
  int time_slice = 5;
  char *test_desc = "two tasks w/ one core, three cycles";
  char *test_str = "simulate_cores/testE";

  helper(num_tasks, INITIAL_HEAP_SIZE, task_order,
	 tasks, num_cores, time_slice, 3, test_desc, test_str);
}

Test(simulate_cores, testF) 
{
  int num_tasks = 2;
  task_t tasks[] = {{0, 2, 10}, {1, 2, 5}};
  int task_order[] = {1, 0};
  int num_cores = 2;
  int time_slice = 10;
  char *test_desc = "two tasks w/ one core, three cycles";
  char *test_str = "simulate_cores/testF";

  helper(num_tasks, INITIAL_HEAP_SIZE, task_order,
	 tasks, num_cores, time_slice, 1, test_desc, test_str);
}

Test(simulate_cores, testG) 
{
  int num_tasks = 2;
  task_t tasks[] = {{0, 2, 10}, {1, 2, 5}};
  int task_order[] = {1, 0};
  int num_cores = 2;
  int time_slice = 5;
  char *test_desc = "two tasks w/ one core, three cycles";
  char *test_str = "simulate_cores/testG";

  helper(num_tasks, INITIAL_HEAP_SIZE, task_order,
	 tasks, num_cores, time_slice, 2, test_desc, test_str);
}

Test(simulate_cores, testH) 
{
  int num_tasks = 2;
  task_t tasks[] = {{0, 2, 10}, {1, 2, 5}};
  int task_order[] = {1, 0};
  int num_cores = 2;
  int time_slice = 4;
  char *test_desc = "two tasks w/ one core, three cycles";
  char *test_str = "simulate_cores/testH";

  helper(num_tasks, INITIAL_HEAP_SIZE, task_order,
	 tasks, num_cores, time_slice, 3, test_desc, test_str);
}

Test(simulate_cores, testI)
{
    int num_tasks = 4;
    task_t tasks[] = {{0, 1, 20}, {1, 2, 10}, {2, 2, 10}, {3, 2, 5}};
    int task_order[] = {3, 1, 2, 0};
    int time_slice = 6;
    int num_cores = 2;
    char *test_desc = "Example from writeup";
    char *test_str = "simulate_cores/testI";
    int heap_size = INITIAL_HEAP_SIZE;

    helper(num_tasks, heap_size, task_order,
	   tasks, num_cores, time_slice, 6, test_desc, test_str);
}


Test(simulate_cores, testJ) 
{
    int num_tasks = 9;
    task_t tasks[] = {{0, 10, 5}, {1, 8, 10}, {2, 8, 5}, {3, 7, 10}, {4, 7, 10}, 
		      {5, 6, 5}, {6, 5, 3}, {7, 9, 10}, {8, 12, 10}};
    int task_order[] = {8, 0, 2, 7, 4, 5, 6, 3, 1};
    int num_cores = 1;
    int time_slice = 10;
    char *test_desc = "two tasks w/ one core, three cycles";
    char *test_str = "simulate_cores/testJ";
    int heap_size = INITIAL_HEAP_SIZE*GROWTH_MULTIPLIER;

    helper(num_tasks, heap_size, task_order,
	   tasks, num_cores, time_slice, 9, test_desc, test_str);
}

Test(simulate_cores, testK) 
{
    int num_tasks = 9;
    task_t tasks[] = {{0, 10, 5}, {1, 8, 10}, {2, 8, 5}, {3, 7, 10}, {4, 7, 10}, 
		      {5, 6, 5}, {6, 5, 3}, {7, 9, 10}, {8, 12, 10}};
    int task_order[] = {8, 0, 2, 7, 4, 5, 6, 3, 1};
    int num_cores = 1;
    int time_slice = 5;
    char *test_desc = "two tasks w/ one core, three cycles";
    char *test_str = "simulate_cores/testK";
    int heap_size = INITIAL_HEAP_SIZE*GROWTH_MULTIPLIER;

    helper(num_tasks, heap_size, task_order,
	   tasks, num_cores, time_slice, 14, test_desc, test_str);
}

Test(simulate_cores, testL) 
{
    int num_tasks = 9;
    task_t tasks[] = {{0, 10, 5}, {1, 8, 10}, {2, 8, 5}, {3, 7, 10}, {4, 7, 10}, 
		      {5, 6, 5}, {6, 5, 3}, {7, 9, 10}, {8, 12, 10}};
    int task_order[] = {8, 0, 2, 7, 4, 5, 6, 3, 1};
    int num_cores = 10;
    int time_slice = 10;
    char *test_desc = "two tasks w/ one core, three cycles";
    char *test_str = "simulate_cores/testL";
    int heap_size = INITIAL_HEAP_SIZE*GROWTH_MULTIPLIER;

    helper(num_tasks, heap_size, task_order,
	   tasks, num_cores, time_slice, 1, test_desc, test_str);
}

Test(simulate_cores, testM) 
{
    int num_tasks = 9;
    task_t tasks[] = {{0, 10, 5}, {1, 8, 10}, {2, 8, 5}, {3, 7, 10}, {4, 7, 10}, 
		      {5, 6, 5}, {6, 5, 3}, {7, 9, 10}, {8, 12, 10}};
    int task_order[] = {8, 0, 2, 7, 4, 5, 6, 3, 1};
    int num_cores = 3;
    int time_slice = 5;
    char *test_desc = "two tasks w/ one core, three cycles";
    char *test_str = "simulate_cores/testM";
    int heap_size = INITIAL_HEAP_SIZE*GROWTH_MULTIPLIER;

    helper(num_tasks, heap_size, task_order,
	   tasks, num_cores, time_slice, 5, test_desc, test_str);
}

Test(simulate_cores, testN) 
{
    int num_tasks = 9;
    task_t tasks[] = {{0, 10, 5}, {1, 8, 10}, {2, 8, 5}, {3, 7, 10}, {4, 7, 12}, 
		      {5, 6, 5}, {6, 5, 3}, {7, 9, 10}, {8, 12, 8}};
    int task_order[] = {8, 0, 2, 7, 4, 5, 6, 3, 1};
    int num_cores = 3;
    int time_slice = 4;
    char *test_desc = "two tasks w/ one core, three cycles";
    char *test_str = "simulate_cores/testN";
    int heap_size = INITIAL_HEAP_SIZE*GROWTH_MULTIPLIER;

    helper(num_tasks, heap_size, task_order,
	   tasks, num_cores, time_slice, 7, test_desc, test_str);
}


Test(simulate_cores, testO) 
{
    int num_tasks = 11;
    task_t tasks[] = {{0, 10, 5}, {1, 8, 10}, {2, 8, 5}, {3, 7, 10}, {4, 7, 10}, 
		      {5, 6, 5}, {6, 5, 3}, {7, 9, 10}, {8, 12, 10}, {9, 1, 4}, {10, 1, 5}};
    int task_order[] = {8, 0, 2, 7, 4, 5, 6, 3, 1, 9, 10};
    int num_cores = 3;
    int time_slice = 4;
    char *test_desc = "Simulate 11 tasks on three cores";
    char *test_str = "simulate_cores/testO)";

    int heap_size = INITIAL_HEAP_SIZE*GROWTH_MULTIPLIER*GROWTH_MULTIPLIER;

    helper(num_tasks, heap_size, task_order,
	   tasks, num_cores, time_slice, 9, test_desc, test_str);
}


Test(simulate_cores, testP)
{
    int num_tasks = 4;
    task_t tasks[] = {{0, 1, 4}, {1, 2, 10}, {2, 2, 10}, {3, 2, 10}};
    int task_order[] = {1, 3, 2, 0};
    int time_slice = 6;
    int num_cores = 3;
    char *test_desc = "Example where all the tasks stay from one cycle to the next";
    char *test_str = "simulate_cores/testP";
    int heap_size = INITIAL_HEAP_SIZE;

    helper(num_tasks, heap_size, task_order,
	   tasks, num_cores, time_slice, 3, test_desc, test_str);
}
