/* CMSC 15200, Winter 2021
 * PA #3 Task Manager: Source file for task manager
 * FLYNN RICHARDSON
 */

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#include "task_manager.h"

/********* Do NOT modify the type definitions *********/

/* Doubly-linked list (DLL) of tasks */
typedef struct dll_node dll_t;
 
/* Definition of the nodes for doubly-lined list of tasks.
 * DLL must have a dummy head node and be circular: the next field in the last 
 * node in the list should point to the dummy node and the prev field of 
 * the dummy node points to the last node in the list.  An empty list will have
 * exactly one node (the dummy node) with pointers back to itself for 
 * both the next and prev fields. 
 */
struct dll_node {
    int tid;      // task identifier
    int priority; // task priority
    int run_time; // task run-time
    dll_t *next;  // next node in the list
    dll_t *prev;  // previous node in the list
};

/* Structure definition for the task manager */
struct task_manager {
    dll_t *task_list;
    int max_priority;
    int next_tid;
};

/********* End type definitions *********/


/* tm_create: create an empty task manager
 *
 * max_priority: task priorities will run from 0 to max_priority (inclusive).
 *
 * Returns: task manager
 */
task_manager_t *tm_create(int max_priority)
{
    task_manager_t* empty_task_manager = (task_manager_t*)malloc(max_priority * sizeof(task_manager_t));
    empty_task_manager->max_priority = max_priority;
    empty_task_manager->next_tid = 0;
    
    empty_task_manager->task_list = (dll_t*)malloc(sizeof(dll_t));
    empty_task_manager->task_list->next = empty_task_manager->task_list;
    empty_task_manager->task_list->prev = empty_task_manager->task_list;

    return empty_task_manager;
}


/* tm_free: free all the space associated with a task manager
 *
 * tm: a task manager
 */
void tm_free(task_manager_t *tm)
{
    // Your code here.
}

/* tm_print: (optional) print the contents of the task manager list 
 *
 * tm: a task manager
 */
void tm_print(task_manager_t *tm)
{
    printf("%d\n", tm->max_priority);
    printf("%d\n", tm->next_tid);
    for (int i = 0; i < tm->next_tid; i++) 
    {
        printf("%d", tm->task_list->tid);
        printf("%d", tm->task_list->priority);
        printf("%d", tm->task_list->run_time);
    }
}


/* tm_is_empty: is the task manager empty?
 *
 * tm: a task manager
 *
 * Returns: true is there are zero tasks on the task list,
 *  false otherwise.
 */
bool tm_is_empty(task_manager_t *tm)
{
    return false;
}
/* tm_add_task: add a new task with the specified priority and
 *   running time to the end of the task list.
 *
 * tm: a task manager
 * priority: the priority for the task (must be between 0 and
 *  the maximum priority specified in the task manager (inclusive)
 * run_time: the running time of the task
 *
 * Returns: a unique identifier for the task as an integer
 */
int tm_add_task(task_manager_t *tm, int priority, int run_time)
{
    /* Allocate space for new task and update its data fields */
    dll_t* task = (dll_t*)malloc(sizeof(dll_t));
    task->priority = priority;
    task->run_time = run_time;

    /* Update pointers and task identifier for an empty task list */
    if (tm->task_list->next == tm->task_list) 
    {
        tm->task_list->next = task;
        tm->task_list->prev = task;
        task->next = tm->task_list;
        task->prev = tm->task_list;
        task->tid = 0; // I made this 0 because it would be the first element in the list
    }

    /* Traverse list to last element before dummy node and update pointers accordingly */
    dll_t* dummy_node = tm->task_list; // keeps track of list position
    task->next = tm->task_list;
    tm->task_list->prev = task;
    task->tid = 0;

    while (tm->task_list->next != dummy_node)
    {
        tm->task_list = tm->task_list->next;
        task->tid++;
    }
    
    tm->task_list->next = task;
    task->prev = tm->task_list;
    tm->next_tid++; //Increment next_tid by 1

    return task->tid;

}


/* tm_remove_task: remove the specified task from the task manager if
 *   it exists
 *
 * tm: a task manager
 * tid: a task identifier
 *
 * Returns: true if task with task identifier tid has been removed from the list,
 *  false if no such task existed
 */
bool tm_remove_task(task_manager_t *tm, int tid)
{
    // Your code here.
    // Replace false with an appropriate return value
    return false;
}


/* tm_get_num_tasks: return the number of tasks on the list
 *
 * tm: a task manager
 *
 * Returns: the number of tasks on the list as an integer
 */
int tm_get_num_tasks(task_manager_t *tm)
{
    // Your code here.
    // Replace 0 with an appropriate return value
    return 0;
}


/* tm_get_max_priority: get the maximum priority associated with a task manager
 *
 * tm: a task manager
 *
 * Returns: returns the maximum priority associated with a task manager as an integer
 */
int tm_get_max_priority(task_manager_t *tm)
{
    // Your code here.
    // Replace 0 with an appropriate return value
    return 0;
}


/* tmp_get_num_jobs_by_priority: count the number of tasks for each priority level
 *
 * tm: a task manager 
 * count_by_priority: the array in which to store the counts.  Must be
 *   big enough to hold counts for prioritys from 0 to the tm's max
 *   priority (inclusive)
 */
void tm_get_num_jobs_by_priority(task_manager_t *tm, int count_by_priority[])
{
    // Your code here.
}


/* tm_run_cycle: Runs each task for the length of time specified for
 *   its priority. Removes tasks that are finished from the task list.
 *
 * tm: a task manager
 * time_slice_per_priority: array with time slices for each
 *   priority. The pth entry is the maximum amount of time to run
 *   a given task of priority p.  Assume there are enough entries
 *   for 0 to the tm's max priority (inclusive).
 * 
 * Returns: the total time executed for the tasks
 */
int tm_run_cycle(task_manager_t *tm, int time_slice_per_priority[])
{
    // Your code here.
    // Replace 0 with an appropriate return value
    return 0;
}
