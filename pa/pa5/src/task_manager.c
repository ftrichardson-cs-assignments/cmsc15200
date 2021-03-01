/* CMSC 15200, Winter 2021
 *  PA #5 Task Manager: Source file for priority queue-based task manager
 */

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#include "task.h"
#include "task_manager.h"

/********* Do NOT modify this code *********/

#define INITIAL_HEAP_SIZE 5
#define GROWTH_MULTIPLIER 2

/* Structure definition for the task manager */
struct task_manager
{
    int next_heap_slot;
    int heap_size;
    task_t **heap;
};

/* swap - swap the contents of two locations
 *
 * p - pointer to a location holding a pointer to a task
 * q - pointer to a location holding a pointer to a task
 *
 */
void swap(task_t **p, task_t **q)
{
    task_t *tmp = *p;
    *p = *q;
    *q = tmp;
}

/********* End of provided code *********/

/********* Helper functions *********/

// Put your helper functions here.

/********* Required functions *********/

/* tm_create: create an empty task manager
 *
 * Returns: a pointer to a task manager
 */
task_manager_t *tm_create()
{
    // YOUR CODE HERE
    // REPLACE NULL WITH AN APPROPRIATE RETURN VALUE
    return NULL;
}

/* tm_free: free all the space associated with a task manager and with any tasks that
 *   are still in the heap.
 *
 * tm: a pointer to a task manager
 *
 */
void tm_free(task_manager_t *tm)
{
    // YOUR CODE HERE
}

/* tm_print: (optional) print the contents of the heap
 *
 * tm: a pointer to a task manager
 *
 */
void tm_print(task_manager_t *tm)
{
    // YOUR CODE HERE
}

/* tm_is_empty: is the task manager empty?
 *
 * tm: a pointer to a task manager
 * 
 * Returns: true is there are no tasks in the heap
 *   false otherwise.
 */
bool tm_is_empty(task_manager_t *tm)
{
    // YOUR CODE HERE
    // REPLACE false WITH AN APPROPRIATE RETURN VALUE
    return false;
}

/* tm_add_task: add a new task to the task manager
 *
 * tm: a pointer to a task manager
 * task: a pointer to a task
 *
 */
void tm_add_task(task_manager_t *tm, task_t *task)
{
    assert(tm != NULL);

    // YOUR CODE HERE
}

/* tm_remove_most_urgent: remove the most urgent task
 *
 * tm: a pointer to a task manager
 *
 * Return: a pointer to the most urgent task or NULL if the task
 *   manager has no tasks.
 */
task_t *tm_remove_most_urgent_task(task_manager_t *tm)
{
    assert(tm != NULL);

    // YOUR CODE HERE
    // REPLACE NULL WITH AN APPROPRIATE RETURN VALUE

    return NULL;
}
