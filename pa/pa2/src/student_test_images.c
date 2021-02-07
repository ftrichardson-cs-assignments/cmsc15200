#include <stdio.h>
#include <stdlib.h>

#include "util.h"
#include "images.h"

/* Add your test functions (if any) here */

int main()
{
    // Brian Kernighan image
    ppm_t *kernighan;
    kernighan = read_ppm("images/brian_kernighan.ppm");

    // test negative
    ppm_t *kernighan_neg = create_negative(kernighan);
    write_ppm("images/brian_kernighan_negative.ppm", kernighan_neg);

    // free ppms
    free_ppm(kernighan);
    free_ppm(kernighan_neg);
}

