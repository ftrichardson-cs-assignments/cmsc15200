#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "task.h"

int main()
{
    task_t *t0 = mk_task(0, 1, 20);
    task_t *t1 = mk_task(1, 2, 10);
    task_t *t2 = mk_task(2, 2, 5);
    task_t *t3 = mk_task(3, 2, 5);

    print_task(t0);
    print_task(t1);
    print_task(t2);
    print_task(t3);

    printf("t0 ? t1: %d\n", cmp_task(t0, t1));
    printf("t1 ? t0: %d\n", cmp_task(t1, t0));
    printf("t1 ? t2: %d\n", cmp_task(t1, t2));
    printf("t2 ? t1: %d\n", cmp_task(t2, t1));
    printf("t2 ? t3: %d\n", cmp_task(t2, t3));

    int et;
    printf("execute t0 w/ 10: %d", execute_task(t0, 10, &et));
    printf("  et: %d  ", et);
    print_task(t0);

    printf("execute t0 w/ 5: %d", execute_task(t0, 5, &et));
    printf("  et: %d  ", et);
    print_task(t0);

    printf("execute t0 w/ 3: %d", execute_task(t0, 3, &et));
    printf("  et: %d  ", et);
    print_task(t0);

    printf("execute t0 w/ 3: %d", execute_task(t0, 3, &et));
    printf("  et: %d  ", et);
    print_task(t0);

    free_task(t0);
    free_task(t1);
    free_task(t2);
    free_task(t3);
}
