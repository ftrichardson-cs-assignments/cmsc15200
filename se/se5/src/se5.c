#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

#include "se5.h"

/* make_tree_node: makes one node of a tree
 *
 * val: value at the node
 * left: left child of the node (a tree)
 * right: right child of the node (a tree)
 * 
 * Returns: a pointer to a tree
 */ 
inttree_t* make_tree_node(int val, inttree_t* left, inttree_t* right) 
{ 
    inttree_t* t = (inttree_t*)malloc(sizeof(inttree_t));
    if (t == NULL) {
        fprintf(stderr, "make_tree_node: cannot allocate\n");
        exit(1); 
    }

    t->val = val; 
    t->left = left; 
    t->right = right;
    return t; 
}

 /* path_adds_to: find whether a tree has a path of nodes from
 *     root to leaf whose values adds to num
 * 
 * t: a pointer to the tree
 * num: the target sum of values of nodes on a path
 * 
 * Returns: true if path exists, false otherwise
 */ 
bool path_adds_to(inttree_t *t, int num)
{
    // Base case
    if (t == NULL) 
    {
        return num == 0;
    }

    int path_sum = num - t->val;
    return path_adds_to(t->right, path_sum) || path_adds_to(t->left, path_sum);
}

/* preorder_h: helper function for preorder()
 * 
 * t: a pointer to the tree
 * num: the value to find
 * found: boolean indicating if num found in tree
 * 
 * Returns: the number of steps to find num
 */
int preorder_h(inttree_t* t, int num, bool *found) 
{
    if (t == NULL) 
    {
        return 0;
    }

    if (t->val == num) 
    {
        *found = true;
        return 1;
    }

    int left = preorder_h(t->left, num, found);
    if (*found)
    {
        return left + 1;
    }

    int right = preorder_h(t->right, num, found);
    return left + right + 1;
}

/* preorder: search for a value in a tree using
 *     preorder traversal 
 * 
 * t: a pointer to the tree
 * num: the value to find
 * 
 * Returns: the number of steps to find num
 */ 
int preorder(inttree_t *t, int num)
{
    bool found;

    int steps = preorder_h(t, num, &found);
    return steps;
}

/* inorder_h: helper function for inorder()
 *
 * t: a pointer to the tree
 * num: the value to find
 * found: boolean indicating if num found in tree
 *
 * Returns: the number of steps to find num
 */
int inorder_h(inttree_t *t, int num, bool *found) 
{
    if (t == NULL) 
    {
        return 0;
    } 

    int left = inorder_h(t->left, num, found);
    if (*found) 
    {
        return left;
    }

    if (t->val == num) 
    {
        *found = true;
        return left + 1;
    }

    int right = inorder_h(t->right, num, found);
    return left + right + 1;
}

/* inorder: search for a value in a tree using
 *     inorder traversal 
 * 
 * t: a pointer to the tree
 * num: the value to find
 * 
 * Returns: the number of steps to find num
 */ 
int inorder(inttree_t *t, int num)
{
    bool found;
    int steps = inorder_h(t, num, &found);
    return steps;
}

/* minValue: find minimum value in binary search tree
 *
 * t: a pointer to the tree
 *
 * Returns: minimum value in tree
 */
int minValue(inttree_t *t) 
{
    inttree_t* curr = t;

    while (curr->left != NULL) 
    {
        curr = curr->left;
    }
    return curr->val;
}

/* maxValue: find maximum value in binary search tree
 *
 * t: a pointer to the tree
 *
 * Returns: maximum value in tree
 */
int maxValue(inttree_t *t) 
{
    inttree_t* curr = t;

    while (curr->right != NULL) 
    {
        curr = curr->right;
    }
    return curr->val;
}

/* is_not_bst: find whether a tree is not a 
 *     binary search tree
 * 
 * t: a pointer to the tree
 * 
 * Returns: true if t is not a BST, false otherwise
 */ 
bool is_not_bst(inttree_t *t) 
{
    if (t == NULL) 
    {
        return false;
    }

    if ((t->left != NULL && maxValue(t->left) > t->val) || 
        (t->right != NULL && minValue(t->right) < t->val)) 
    {
        return true;
    }

    return is_not_bst(t->left) || is_not_bst(t->right);
}