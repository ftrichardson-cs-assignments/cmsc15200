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
    *total_time_ptr = 0;
    int num_cycles = 0;
    task_t** cores = (task_t**)malloc(num_cores * sizeof(task_t*));

    // Set every element in cores to NULL
    for (int n = 0; n < num_cores; n++) 
    {
        cores[n] = NULL;
    }

    while (!tm_is_empty(tm)) 
    {
        // Fill cores
        for (int n = 0; n < num_cores; n++) 
        {
            if (cores[n] == NULL) 
            {
                cores[n] = tm_remove_most_urgent_task(tm);
            }
        }

        // Execute tasks
        for (int n = 0; n < num_cores; n++) 
        {
            int execution_time;

            if (cores[n] == NULL) 
            {
                continue;
            }

            enum task_status status = execute_task(cores[n], time_slice, &execution_time);
            *total_time_ptr += execution_time;

            if (status == TASK_DONE) 
            {
                free(cores[n]);
                cores[n] = NULL;
            }

            if (status == TASK_RESCHEDULE) 
            {
                tm_add_task(tm, cores[n]);
                cores[n] = NULL;
            }

            if (status == TASK_KEEP) 
            {
                continue;
            }
        }
        num_cycles++;
    }

    // Check for any task remaining in core once task manager empty
    for (int n = 0; n < num_cores; n++) 
    {
        if (cores[n] != NULL) 
        {
            int execution_time;
            enum task_status status = execute_task(cores[n], time_slice, &execution_time);
            *total_time_ptr += execution_time;
            num_cycles++;
        }
    }
    return num_cycles;
}
