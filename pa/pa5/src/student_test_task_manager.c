#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "task.h"
#include "task_manager.h"

int main()
{
    task_t *t0 = mk_task(0, 1, 20);
    task_t *t1 = mk_task(1, 2, 10);
    task_t *t2 = mk_task(2, 2, 5);
    task_t *t3 = mk_task(3, 2, 5);

    task_manager_t *tm = tm_create();
    tm_add_task(tm, t0);
    tm_add_task(tm, t1);
    tm_add_task(tm, t2);
    tm_add_task(tm, t3);

    printf("\n");
    printf("After adding\n");
    printf("\n");
    tm_print(tm);

    printf("\n");
    printf("Removing...\n");
    task_t* most_urgent_task = tm_remove_most_urgent_task(tm);
    printf("\n");
    print_task(most_urgent_task);
    printf("\n");
    tm_print(tm);
    printf("\n");
}
