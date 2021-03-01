/* CMSC 15200, Winter 2021
 *  PA #4 Trie: Source for PA #4.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>

#include "trie.h"

#define max(i, j) (i > j ? i : j) // used in add_word()

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
    for (int i = 0; i < NUM_CHARACTERS; i++) 
    {
        trie->next[i] = NULL;
    }
    
    return trie;
}

/* Free a trie
 *
 * trie: a pointer to the trie
 */ 
void free_trie(tnode_t *trie)
{
    for (int i = 0; i < NUM_CHARACTERS; i++)
    {
        if (trie->next[i] != NULL) 
        {
            free_trie(trie->next[i]);
        }
    }
    free(trie);
}

/* Add a word to a trie
 *
 * trie: a pointer to the trie
 * word: the word to add
 */
void add_word(tnode_t *trie, char *word)
{
    trie->count++;
    trie->longest = max(trie->longest, strlen(word));

    for (int n = 0; n < strlen(word); n++)
    {
        char letter = word[n];
        int ASCII = (int) letter - (int) 'a';
        int len_completion = strlen(word) - (n + 1);

        if (trie->next[ASCII] == NULL)
        {
            trie->next[ASCII] = create_trie_node();
            trie->next[ASCII]->count++;
            trie->next[ASCII]->longest = len_completion;

        } else 
        {
            trie->next[ASCII]->count++;
            trie->next[ASCII]->longest = max(trie->next[ASCII]->longest, len_completion);
        }

        /* Validate trie->next[ASCII] once end of word reached */
        if (n == strlen(word) - 1) 
        {
            trie->next[ASCII]->final = true;
        }

        trie = trie->next[ASCII];
    }
}

/* traverse_trie: traverses a trie
 * 
 * trie: a pointer to the trie
 * prefix: the prefix to complete
 *
 * Returns: pointer to trie according to prefix
 */
tnode_t *traverse_trie(tnode_t* trie, char *prefix) 
{
    if (!strcmp(prefix, "")) 
    {
        return trie;
    }
    
    for (int n = 0; n < strlen(prefix); n++) 
    {
        char letter = prefix[n];
        int ASCII = (int) letter - (int) 'a';

        if (trie->next[ASCII] == NULL && !trie->final) 
        {
            break;
        }

        if (n == strlen(prefix) - 1)
        {
            return trie->next[ASCII];
        }

        trie = trie->next[ASCII];

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
    tnode_t* word_trie = traverse_trie(trie, word);
    
    if (!word_trie) 
    {
        return false;
    }

    return word_trie->final;
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
    tnode_t* prefix_trie = traverse_trie(trie, prefix);
   
    if (!prefix_trie) 
    {
        return 0;
    }

    return prefix_trie->count;
}

/* Fills array (helper to get_completions)
 * 
 * trie: a pointer to the trie
 * temp_string: array to hold strings
 * completions: array to hold completions
 * index_ptr: index for completions
 */
void completions_array(tnode_t* trie, char *temp_string, int str_index, char **completions, int *index_ptr) 
{
    if (trie->count == 1 && trie->final)
    {
        temp_string[str_index] = '\0';
        char* perm_string = (char*)malloc((str_index + 2) * sizeof(char));
        strcpy(perm_string, temp_string);
        completions[*index_ptr] = perm_string;
        (*index_ptr)++;
        return;
    }
  
    if (trie->final)
    {
        temp_string[str_index] = '\0';
        char* perm_string = (char*)malloc((str_index + 2) * sizeof(char));
        strcpy(perm_string, temp_string);
        completions[*index_ptr] = perm_string;
        (*index_ptr)++;
    }
  
    for (int n = 0; n < NUM_CHARACTERS; n++)
    {
        char letter = (char) (n + (int) 'a');
        
        if (trie->next[n])
        {
            temp_string[str_index] = letter;
            completions_array(trie->next[n], temp_string, str_index + 1, completions, index_ptr);
        }
    }
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
    tnode_t* prefix_trie = traverse_trie(trie, prefix);
  
    if (!prefix_trie) 
    {
        return NULL;
    }
  
    int index = 0;
    int str_index = 0;
    char** completions = (char**)malloc(num_completions(trie, prefix) * sizeof(char*));
    char* temp_string = (char*)malloc((prefix_trie->longest + 1) * sizeof(char));
  
    completions_array(prefix_trie, temp_string, str_index, completions, &index);
  
    return completions;
}