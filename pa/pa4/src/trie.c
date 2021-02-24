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
    tnode_t* trie = (tnode_t*)malloc(sizeof(tnode_t));
    trie->final = false;
    trie->count = 0;
    trie->longest = 0;
    
    return trie;
}

/* Free a trie
 *
 * trie: a pointer to the trie
 */ 
void free_trie(tnode_t *trie)
{
    if (!trie)
    {
        return;
    }

    for (int i = 0; i < NUM_CHARACTERS; i++)
    {
        free_trie(trie->next[i]);
    }
    free(trie);
}

int longest_completion(int i, int j)
{
    if (i <= j)
    {
        return j;
    }    

    return i;
}

int letter_to_index(char letter)
{
    return (int) letter - (int) 'a';
}

/* Add a word to a trie
 *
 * trie: a pointer to the trie
 * word: the word to add
 */

void add_word(tnode_t *trie, char *word)
{
    trie->count++;
    trie->longest = longest_completion(trie->longest, strlen(word));

    for (int n = 0; n < strlen(word); n++)
    {
        char letter = word[n];
        int letter_index = letter_to_index(letter);
        int completion_length = strlen(word) - (n + 1);

        if (trie->next[letter_index] == NULL)
        {
            trie->next[letter_index] = create_trie_node();
            trie->next[letter_index]->count++;
            trie->next[letter_index]->longest = completion_length;
        } else 
        {
            trie->next[letter_index]->count++;
            trie->next[letter_index]->longest = longest_completion(trie->next[letter_index]->longest, completion_length);
        }

        if (n == strlen(word) - 1) 
        {
            trie->next[letter_index]->final = true;
        }

        trie = trie->next[letter_index];
    }
}

tnode_t *prefix_trie(tnode_t* trie, char *prefix) 
{
    for (int n = 0; n < strlen(prefix); n++) 
    {
        char letter = prefix[n];
        int letter_index = letter_to_index(letter);

        if (trie->next[letter_index] == NULL && !trie->final) 
        {
            break;
        }

        if (n == strlen(prefix) - 1)
        {
            return trie->next[letter_index];
        }

        trie = trie->next[letter_index];

    }
    return NULL;
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
    for (int n = 0; n < strlen(word); n++)
    {
        char letter = word[n];
        int letter_index = letter_to_index(letter);

        if (trie->next[letter_index] == NULL)
        {
            return false;
        }

        if (n == strlen(word) - 1) 
        {
            return trie->next[letter_index]->final;
        }

        trie = trie->next[letter_index];
    }
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
    for (int n = 0; n < strlen(prefix); n++) 
    {
        char letter = prefix[n];
        int letter_index = letter_to_index(letter);

        if (trie->next[letter_index] == NULL && !trie->final) 
        {
            break;
        }

        if (n == strlen(prefix) - 1)
        {
            return trie->next[letter_index]->count;
        }

        trie = trie->next[letter_index];
    }
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
    int len_completions = num_completions(trie, prefix);
    char** completions = (char**)malloc((len_completions + 1) * sizeof(char*));

    if (len_completions == 0)
    {
        return completions;
    }
    
    for (int n = 0; n < len_completions; n++)
    {

    }

}
