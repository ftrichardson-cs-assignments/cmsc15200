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

void double_heap_size(task_manager_t* tm) 
{
    // GROWTH_MULTIPLIER doubles current heap size
    
    tm->heap = (task_t**)realloc(tm->heap, tm->heap_size * GROWTH_MULTIPLIER * sizeof(task_t*));
    tm->heap_size *= GROWTH_MULTIPLIER;
}

void sift_up(task_manager_t* tm) 
{
    int index = tm->next_heap_slot;

    while (index > 0) 
    {
        int parent = (index - 1) / 2;
        if (cmp_task(tm->heap[index], tm->heap[parent]) < 0)
        {
            swap(&tm->heap[index], &tm->heap[parent]);

        } else 
        {
            break; // No need to continue if swap not executed
        }
        index = parent;
    }
}

void sift_down(task_manager_t *tm) 
{
    int index = 0;
    int left = 2 * index + 1;
    int right = 2 * index + 2;

    while (left < tm->next_heap_slot) 
    {
        int most_urgent_index = left;

        if (cmp_task(tm->heap[right], tm->heap[left]) < 0) 
        {
            most_urgent_index = right;
        }

        if (cmp_task(tm->heap[index], tm->heap[most_urgent_index]) < 0)
        {
            break; // No need to continue if current task is more urgent than children

        } else 
        {
            swap(&tm->heap[index], &tm->heap[most_urgent_index]);
        }

        index = most_urgent_index;
        left = (2 * index) + 1;
        right = (2 * index) + 2;
    }
}

/********* Required functions *********/

/* tm_create: create an empty task manager
 *
 * Returns: a pointer to a task manager
 */
task_manager_t *tm_create()
{
    task_manager_t* empty_tm = (task_manager_t*)malloc(sizeof(task_manager_t));

    if (empty_tm == NULL) 
    {
        fprintf(stderr, "tm_create: not enough space for *task_manager_t\n");
        exit(1);
    }
    empty_tm->next_heap_slot = 0;
    empty_tm->heap_size = INITIAL_HEAP_SIZE;
    empty_tm->heap = (task_t**)malloc(sizeof(task_t*) * INITIAL_HEAP_SIZE);

    if (empty_tm->heap == NULL) 
    {
        fprintf(stderr, "tm_create: not enough space for **task_t\n");
        exit(1);
    }
    
    return empty_tm;
}

/* tm_free: free all the space associated with a task manager and with any tasks that
 *   are still in the heap.
 *
 * tm: a pointer to a task manager
 *
 */
void tm_free(task_manager_t *tm)
{
    for (int n = 0; n < tm->next_heap_slot; n++) 
    {
        free(tm->heap[n]); // Added tasks != NULL, so no need to check if NULL 
    }
    free(tm->heap);
    free(tm);
}

/* tm_print: (optional) print the contents of the heap
 *
 * tm: a pointer to a task manager
 *
 */
void tm_print(task_manager_t *tm)
{
    printf("Task Manager\n");
    printf("---------\n");
    printf("next_heap_slot : %d\n", tm->next_heap_slot);
    printf("heap_size : %d\n", tm->heap_size);
    printf("heap :");
    printf("\n");
    
    for (int n = 0; n < tm->next_heap_slot; n++) 
    {
        printf("\n");
        print_task(tm->heap[n]);
        printf("\n");
    }
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
    return tm->next_heap_slot == 0;
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

    if (tm_is_empty(tm)) 
    {
        tm->heap[tm->next_heap_slot] = task;
    }
    
    if (tm->heap_size == tm->next_heap_slot) 
    {
        double_heap_size(tm);
    }

    tm->heap[tm->next_heap_slot] = task;
    sift_up(tm);
    tm->next_heap_slot++;
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

    if (tm_is_empty(tm))
    {
        return NULL;
    }

    task_t* most_urgent_task = tm->heap[0];
    tm->heap[0] = tm->heap[tm->next_heap_slot - 1]; // Add last value in heap to root
    tm->next_heap_slot--; // Decrement number of elements in heap
    sift_down(tm);

    return most_urgent_task;
}
