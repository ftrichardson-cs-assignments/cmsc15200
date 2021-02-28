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
   
    if (!strcmp(prefix, ""))
    {
        return trie->count;
    }
     
    if (!prefix_trie) 
    {
        return 0;
    }

    return prefix_trie->count;
}



/* The get_completions function I am struggling with greatly because recursion is still a
concept that I struggle to understand, especially with more complex applications
of recursion. I have commented some of my code so that it will be easier to see where 
I am misunderstanding my code and/or my logic to solve this problem is wrong. I think if I'm
able to solve this problem myself, the concept will be much clearer to me, so any hints you could give me
about my implementation would be greatly appreciated! Thank you!!! */

void completions_array(tnode_t* trie, char *temp_str, char **completions, int *index_ptr) 
{
    if (!trie) //Base case (if trie->next[n] == NULL then !trie is true)
    {
        return;
    }
     
    int temp_str_index = 0; //Separate index for temp_string

    for (int n = 0; n < NUM_CHARACTERS; n++)
    {
        completions_array(trie->next[n], temp_string, completions, index_ptr); //Is this where I should be recursing?
        char letter = (char) (n + (int) 'a');
        
        if (trie->next[n] != NULL && !trie->final)
        {
            temp_string[temp_str_index] = letter;
            temp_str_index++;
        }

        if (trie->next[n] == NULL && trie->final)
        {
            temp_string[str_index] = letter;
            temp_string[str_index + 1] = '\0';
            temp_string = realloc(temp_string, (strlen(temp_string) + 1) * sizeof(char));
            completions[*index_ptr] = temp_string;
            (*index_ptr)++;
        }

        /*I know this code doesn't currently handle a case such as "the" if "their" is in trie, but I 
        want to make sure I understand the recursion first before proceeding */
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
    tnode_t* prefix_trie = traverse_trie(trie, prefix); // Brings me to the correct trie
    char** completions = (char**)malloc(num_completions(trie, prefix) * sizeof(char*));
    char* temp_string = (char*)malloc((prefix_trie->longest + 1) * sizeof(char));
    int index = 0; // Index for completions

    if (prefix && !prefix_trie)
    {
        return NULL; //Case of NO completions
    }

    completions_array(prefix_trie, temp_string, completions, &index);

    return completions; //After call, I return the filled array (which obviously is not currently accurate)
}