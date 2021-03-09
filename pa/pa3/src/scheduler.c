/* CMSC 15200, Winter 2021
 *  PA #3 Task Manager: Source file for a task scheduler
 */

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "task_manager.h"
#include "scheduler.h"

/* run_tasks: finds the number of cycles to complete for all
 * the tasks to time out
 * 
 * tm: a task manager
 * time_slices: an array with time slices for each priority
 * total_time_ptr: out parameter representing total execution time
 *   for all the tasks to time out
 *
 * Returns: the number of necessary cycles to timeout the tasks
 */
int run_tasks(task_manager_t *tm, int time_slices[], int *total_time_ptr)
{
	int num_cycles = 0;
	*total_time_ptr = 0;

	while (!tm_is_empty(tm)) 
	{
		*total_time_ptr += tm_run_cycle(tm, time_slices);
		num_cycles++;
	}
	return num_cycles;
}