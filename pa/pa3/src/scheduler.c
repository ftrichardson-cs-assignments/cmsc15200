/* CMSC 15200, Winter 2021
 *  PA #3 Task Manager: Source file for a task scheduler
 */

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "task_manager.h"
#include "scheduler.h"

int run_tasks(task_manager_t *tm, int time_slices[], int *total_time_ptr)
{
	int num_tasks = 0;
	*total_time_ptr = 0;

	while (!tm_is_empty(tm)) 
	{
		*total_time_ptr += tm_run_cycle(tm, time_slices);
		num_tasks++;
	}
	return num_tasks;
}


