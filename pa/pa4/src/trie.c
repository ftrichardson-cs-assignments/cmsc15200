/* CMSC 15200, Winter 2021
 *  PA #4 Trie: Source for PA #4.
 */




#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>

#include "trie.h"

/* Create a new tnode_t
 *
 * Returns: a pointer to a tnode_t
 */ 
tnode_t *create_trie_node()
{
    // YOUR CODE HERE
    return NULL;
}

/* Free a trie
 *
 * trie: a pointer to the trie
 */ 
void free_trie(tnode_t *trie)
{
    // YOUR CODE HERE
}

/* Add a word to a trie
 *
 * trie: a pointer to the trie
 * word: the word to add
 */ 
void add_word(tnode_t *trie, char *word)
{
    // YOUR CODE HERE
}

/* Determine whether a word is in a trie
 *
 * trie: a pointer to the trie
 * word: the word to search for
 * 
 * Returns: whether the word is in the trie
 */ 
bool is_a_word(tnode_t *trie, char *word)
{
    // YOUR CODE HERE
    return false;
}

/* Get the number of completions
 *
 * trie: a pointer to the trie
 * prefix: the prefix to complete
 * 
 * Returns: the number of completions
 */ 
int num_completions(tnode_t *trie, char *prefix)
{
    // YOUR CODE HERE
    return 0;
}


/* Construct the completions of a prefix
 *
 * trie: a pointer to the trie
 * prefix: the prefix to complete
 * 
 * Returns: an array of completion strings
 */ 
char **get_completions(tnode_t *trie, char *prefix)
{
    // YOUR CODE HERE
    return NULL;
}
