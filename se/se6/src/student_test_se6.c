#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "se6.h"

/** Add your test functions (if any) here **/

int main()
{
    

    // create a hash table
    htable_t ht;
    ht.size = 4;
    ht.table = (char **)malloc(sizeof(char*) * ht.size);

    // hash words
    printf("hash('a'): %d\n", hash(ht, "a"));
    printf("hash('b'): %d\n", hash(ht, "b"));

    ht.table[0] = "d";
    ht.table[1] = "a";
    ht.table[2] = "b";
    ht.table[3] = NULL;

    printf("is_full(ht): %d\n", is_full(ht));

    /** Add calls to your functions here **/
}
