#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "task.h"
#include "task_manager.h"
#include "scheduler.h"

int main()
{
    task_t *t0 = mk_task(0, 1, 20);
    task_t *t1 = mk_task(1, 2, 10);
    task_t *t2 = mk_task(2, 2, 10);
    task_t *t3 = mk_task(3, 2, 5);

    task_manager_t *tm = tm_create();
    tm_add_task(tm, t0);
    tm_add_task(tm, t1);
    tm_add_task(tm, t2);
    tm_add_task(tm, t3);

    int total_time;
    int num_cycles = simulate_cores(tm, 2, 6, &total_time);
    printf("total_time: %d  num_cycles: %d\n", total_time, num_cycles);

    tm_free(tm);
}
