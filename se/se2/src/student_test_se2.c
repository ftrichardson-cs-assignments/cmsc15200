#include <stdio.h>
#include <stdbool.h>
#include <math.h>

#include "se2.h"

/** Add your test functions (if any) here **/

int main()
{
    /** Add calls to your functions here **/
    printf("compute_payoff_amount(100.0, 2.0, 1, 2): %f\n", compute_payoff_amount(100.0, 2.0, 1, 1));
    printf("compute_leonardo(0): %d\n", compute_leonardo(0));
    printf("bakhshali_iterative(100, 20): %f\n", bakhshali_iterative(100, 20));
    printf("bakhshali_recursive(100, 20): %f\n", bakhshali_recursive(100, 20));
}
