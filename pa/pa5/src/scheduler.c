/* CMSC 15200, Winter 2021
 *  PA #5 Task Manager: source file for the PA #5 scheduler
 */

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#include "task.h"
#include "task_manager.h"
#include "scheduler.h"

/********* Helper functions *********/

// Put your helper functions (if any) here.

/********* Required function *********/

/* simulate_cores: simulates task execution in a set of cores
 *
 * tm: a pointer to a task manager w/ a set of tasks to complete
 * num_cores: the number of cores to simulate
 * time_slice: the maximum amount of time a task gets to execute in a
 *   cycle
 * total_time_ptr: an OUT parameter that is used to return the total amount
 *  of time the tasks executed.
 *
 * Returns: the number of cycles needed to complete all the tasks
 */
int simulate_cores(task_manager_t *tm, int num_cores, int time_slice, int *total_time_ptr)
{
    // YOUR CODE HERE
    // REPLACE 0 WITH A SUITABLE RETURN VALUE
    return 0;
}
