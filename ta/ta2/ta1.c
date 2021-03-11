#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/* Use this file for your solution to Timed Assessment #2.1 */
typedef struct dll_node dll_t;

struct dll_node {
    int val;
    dll_t *next;  // points to the next node in the list
    dll_t *prev;  // points to the previous node in the list

};

void print_list(dll_t* head)
{
    dll_t* curr = head->next;
    printf("List value is: %d\n", head->val);

    while (curr != head) 
    {
        printf("List value is: %d\n", curr->val);
        curr = curr->next;
    }

}

dll_t *node_create(int val) 
{
    dll_t* node = (dll_t*)malloc(sizeof(dll_t));
    if (node == NULL) 
    {
        fprintf(stderr, "node_create: malloc failure\n");
        exit(1);
    }

    node->val = val;
    node->next = NULL;
    node->prev = NULL;

    return node;
}

dll_t *mk_list_from_array(int vals[], int num_len) 
{
    if (num_len == 0) 
    {
        return NULL;
    }

    if (num_len == 1) 
    {
        dll_t* node = node_create(vals[0]);
        return node;
    }
    
    dll_t* first = node_create(vals[0]);
    dll_t* second = node_create(vals[1]);
    
    first->next = second;
    second->prev = first;
    
    dll_t* curr = second;

    for (int i = 2; i < num_len; i++) 
    {
        dll_t* node = node_create(vals[i]);
        
        if (i == num_len - 1) 
        {
            curr->next = node;
            node->next = first;
            first->prev = node;
            break;

        } else 
        {
            curr->next = node;
            node->prev = curr;

        }
        curr = curr->next;
    }   
    return first;
}

bool end_point(int size, int cmp_size) 
{
    if (size - cmp_size <= 1 || size - cmp_size >= -1) 
    {
        return true;
    }
    return false;
}

bool is_forward_backward_copy(dll_t *orig, dll_t *possible) 
{
    assert(possible != NULL || orig != NULL);

    if (possible->val != orig->val) 
    {
        return false;
    }
    
    int possible_size = 1;
    int orig_size = 1;

    dll_t* pos_curr = possible;
    dll_t* pos_curr_end = possible;
    dll_t* orig_curr = orig->next;
    
    while (orig_curr != orig) 
    {
        orig_size++;
        orig_curr = orig_curr->next;
    }
    
    while (pos_curr->next != possible) 
    {
        if (orig_curr->val != pos_curr->val || orig_curr->val != pos_curr_end->val) 
        {
            return false;
        }

        if (pos_curr_end == pos_curr || pos_curr_end->next == pos_curr 
            || pos_curr_end->prev == pos_curr) 
        {
            break;
        }

        orig_curr = orig_curr->next;
        pos_curr = pos_curr->next;
        pos_curr_end = pos_curr_end->prev;
        possible_size++;
    }

    if (2 * orig_size != possible_size) 
    {
        return false;
    }

    return true; 
}

int main()
{
	int vals[] = {5, 7, 9, 3};
    dll_t *lst = mk_list_from_array(vals, 4);
    printf("%d", lst->next->val);
}
