#include <stdio.h>
#include <stdlib.h>

#include "se3.h"

/** Add your test functions (if any) here **/

/* 
 * Helper function for student tests
 * Frees a heap allocated array of strings.
 * 
 * a: array of strings
 * a_len: number of elements (length) of array a
 */
void free_star_array(char **a, int a_len){
    for(int i = 0; i < a_len; i++){
        free(a[i]);
    }
    free(a);
}

int main()
{
    /** Add calls to your functions here **/
    printf("make_star_string(4): %s\n", make_star_string(4));
}
