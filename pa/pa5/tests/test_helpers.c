/* CMSC 15200, Winter 2021
 *  PA #5 Task Manager: automated test code
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <criterion/criterion.h>

#include "task.h"
#include "task_manager.h"
#include "util.h"
#include "test_helpers.h"

/* CMSC 15200, Winter 2021
 *  PA #5 Task Manager: automated test code
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <criterion/criterion.h>

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

char *bool_str(bool b) {
    return b ? "true" : "false";
}

void verify_task(task_t *task, task_t expected_task,
		 char *test_desc, char *test_str) {
    cr_assert_neq(task, NULL, "Got an unexpected NULL task\n");

    char err_msg[ERR_MSG_LEN];
    bool match = ((task->tid == expected_task.tid) &&
		  (task->priority == expected_task.priority) &&
		  (task->run_time == expected_task.run_time));
    snprintf(err_msg, (ERR_MSG_LEN-1),
	     ("Test: %s\n"
	      "Tasks do not match (tid, priority, run_time) \n"
	      "  Actual Task (%d, %d, %d)\n"
	      "  Expected Task (%d, %d, %d)\n"
	      "Command to rerun this test: "
	      "bin/test_task_manager --filter %s\n"),
	     test_desc, task->tid, task->priority, task->run_time,	
	     expected_task.tid, expected_task.priority, expected_task.run_time,
	     test_str);
    cr_assert(match, " \n%s", err_msg);
}

void verify_tm(task_manager_t *tm, int num_tasks, int heap_size, int task_order[],
	       task_t tasks[], char *test_desc, char *test_str) {
  cr_assert_neq(tm, NULL, "Got an unexpected NULL task manager\n");
  check_int(tm->next_heap_slot, num_tasks, "Number of Tasks", test_desc, test_str);
  check_int(tm->heap_size, heap_size, "Heap size", test_desc, test_str);

  char *extra_desc = ("\nChecking Heap Order\n"
		      "\nHeap slot %d");
  // 3 is a hack tasks IDs are unlikely to be bigger
  // than three characters
  int len = strlen(test_desc) + strlen(extra_desc) + 3 + 1;
  char task_test_desc[len];

  for (int i = 0; i < num_tasks; i++) {
    snprintf(task_test_desc, len, "%s\nChecking Heap Order\nHeap slot %d", test_desc, i);
    verify_task(tm->heap[i], tasks[task_order[i]], task_test_desc, test_str);
  }
}


void verify_empty_tm(task_manager_t *tm, int expected_heap_size,
		     char *test_desc, char *test_str) {

    verify_tm(tm, 0, expected_heap_size, NULL, 
	      NULL, test_desc, test_str);
}


#define BASIC_MAX_PRIORITY 2


task_manager_t *mk_sample_tm(int num_tasks, int expected_heap_size, int task_order[],
			     task_t tasks[], char *test_desc, char *test_str)
{
    task_manager_t *tm = tm_create();

    char *extra_desc = "\n Constructing Task %d\n";
    int len = strlen(test_desc) + strlen(extra_desc) + 3 + 1;
    char task_test_desc[len];

    for (int i = 0; i < num_tasks; i++) {
      snprintf(task_test_desc, len, "%s\n Constructing Task %d\n", test_desc, i);
      task_t *t = mk_task(tasks[i].tid, tasks[i].priority, tasks[i].run_time);
      verify_task(t, tasks[i], task_test_desc, test_str);
      tm_add_task(tm, t);
    }

    verify_tm(tm, num_tasks, expected_heap_size, task_order,
	      tasks, test_desc, test_str);

    return tm;
}

task_manager_t *mk_zero(char *test_str)
{
  task_manager_t *tm = mk_sample_tm(0, INITIAL_HEAP_SIZE, NULL, 
				    NULL, "Zero tasks", test_str);
  return tm;
}

task_manager_t *mk_one(char *test_str)
{
    int num_tasks = 1;
    task_t tasks[] = {{0, 2, 10}};
    int task_order[] = {0};

    task_manager_t *tm = mk_sample_tm(num_tasks, INITIAL_HEAP_SIZE, task_order,
				      tasks, "One task", test_str);
    return tm;
}
