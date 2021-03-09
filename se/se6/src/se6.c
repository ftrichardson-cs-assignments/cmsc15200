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
    for (int n = 0; n < ht.size; n++) 
    {
        if (ht.table[n] == NULL) 
        {
            return false;
        }
    }
    return true;
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
    int index = hash(ht, s);
    *found = false;

    for (int n = 0; n < ht.size; n++) 
    {
        if (ht.table[n] == s) 
        {
            *found = true;
            return n;
        }

        int possible_index = (n + index) % ht.size;

        if (ht.table[possible_index] == NULL) 
        {
            ht.table[possible_index] = s;
            return possible_index;
        }

    }
    return -1;
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
    bool found;
    found_at(ht, s, &found);
    return found;
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
    bool found;
    int index = found_at(ht, s, &found);

    if (found || index == -1) 
    {
        return false;
    }
    return true;
}