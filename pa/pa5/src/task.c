#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "task.h"

#define KEEP_THRESHOLD 5

/************* Do not change this type ***********/

struct task {
    int tid;      // task identifier
    int priority; // task priority
    int run_time; // task run-time.
};

/************* end type ***********/

/* mk_task: create an new task
 *
 * tid - task ID for the task
 * priorty - priority for the task
 * run_time - running time for the task
 * 
 * Returns: a pointer to a task
 */
task_t *mk_task(int tid, int priority, int run_time)
{
    task_t* new_task = (task_t*)malloc(sizeof(task_t));
    if (new_task == NULL) 
    {
        fprintf(stderr, "mk_task: not enough space\n");
        exit(1);
    }
    new_task->tid = tid;
    new_task->priority = priority;
    new_task->run_time = run_time;

    return new_task;
}

/* free_task: frees the task
 *
 * task - a pointer to a task
 */
void free_task(task_t *task)
{
    assert(task != NULL);
    free(task);
}

/* cmp_task -- determine which of two tasks is more urgent.
 *
 * task1 -- a pointer to a task
 * task2 -- a pointer to a task
 *
 * Returns:
 *   < 0 -- if task1 is more urgent than task2
 *   > 0 -- if task2 is more urgent than task1
 *  == 0 -- if task1 and task2 are equally as urgent
 */
int cmp_task(task_t *task1, task_t *task2)
{
    if (task1->priority > task2->priority ||
       (task1->priority == task2->priority && task1->run_time < task2->run_time))
    {
        return -1;
    }

    if (task2->priority > task1->priority ||
       (task2->priority == task1->priority && task2->run_time < task1->run_time))
    {
        return 1;
    }

    return 0;
}

/* print_task -- optional function that prints the information in a task
 *
 * task -- a pointer to a task
 */
void print_task(task_t *task)
{
    
}

/* execute_task - do one time slice of work for a task
 *
 * task: a pointer to a task
 * time_slice: the maximum amount of time to execute the task in this cycle
 * execution_time_pointer: an OUT parameter for returning the amount of time actually executed.
 *
 * Returns: 
 *   TASK_DONE if the task is finished
 *   TASK_KEEP if the task has less than KEEP_THRESHOLD time left
 *   TASK_RESCHEDULE otherwise
 */
enum task_status execute_task(task_t *task, int time_slice, int *execution_time_ptr)
{
    *execution_time_ptr = 0;
    
    if (task->run_time - time_slice <= 0) 
    {
        int unused_time = -1 * (task->run_time - time_slice);
        *execution_time_ptr += (time_slice - unused_time);
        task->run_time = 0;
        return TASK_DONE;
    }

    *execution_time_ptr += time_slice;
    task->run_time -= time_slice;

    if (task->run_time < KEEP_THRESHOLD) 
    {
        return TASK_KEEP;
    }
    return TASK_RESCHEDULE;
}