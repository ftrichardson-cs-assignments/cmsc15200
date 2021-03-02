#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "se6.h"

/* Hash function
 *
 * ht: hash table
 * s: string to hash
 * 
 * Returns: hash value
 */ 
int hash(htable_t ht, char *s)
{
    int h = 0;
    while(*s) {
        h = h * 37 + (int) (*s++);
        h = h % ht.size;
    }
    return h;
}

/* Determines whether the table is full
 *
 * ht: hash table
 * 
 * Returns: whether or not the table is full
 */ 
bool is_full(htable_t ht)
{
    // YOUR CODE HERE
    return false;
}

/* Determines whether a string is in the hash table or,
 *     if not, where to add it
 *
 * ht: hash table
 * s: query string
 * found: whether or not the string was found (out parameter)
 * 
 * Returns: 
 *     i: string was found at index i
 *     j: string was not found, j is the next open index
 *    -1: string was not found, table is full
 */ 
int found_at(htable_t ht, char *s, bool *found)
{
    // YOUR CODE HERE
    return 0;
}

/* Determines whether a string is in the hash table
 *
 * ht: hash table
 * s: query string
 * 
 * Returns: whether or not the string is in the hash table
 */ 
bool query(htable_t ht, char *s)
{
    // YOUR CODE HERE
    return false;
}

/* Adds string to hash table
 *
 * ht: hash table
 * s: string to add
 * 
 * Returns: whether or not the string was added
 */ 
bool add(htable_t ht, char *s)
{
    // YOUR CODE HERE
    return false;
}