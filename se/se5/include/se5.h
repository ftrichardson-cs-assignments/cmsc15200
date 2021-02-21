typedef struct inttree inttree_t;

struct inttree {
    int val;
    inttree_t *left, *right;
};

/* make_tree_node: makes one node of a tree
 *
 * val: value at the node
 * left: left child of the node (a tree)
 * right: right child of the node (a tree)
 * 
 * Returns: a pointer to a tree
 */ 
inttree_t* make_tree_node(int val, inttree_t* left, inttree_t* right);

/* path_adds_to: find whether a tree has a path of nodes from
 *     root to leaf whose values adds to num
 * 
 * t: a pointer to the tree
 * num: the target sum of values of nodes on a path
 * 
 * Returns: true if path exists, false otherwise
 */ 
bool path_adds_to(inttree_t *t, int num);

/* preorder: search for a value in a tree using
 *     preorder traversal 
 * 
 * t: a pointer to the tree
 * num: the value to find
 * 
 * Returns: the number of steps to find num
 */ 
int preorder(inttree_t *t, int num);

/* inorder: search for a value in a tree using
 *     inorder traversal 
 * 
 * t: a pointer to the tree
 * num: the value to find
 * 
 * Returns: the number of steps to find num
 */ 
int inorder(inttree_t *t, int num);

/* is_not_bst: find whether a tree is not a 
 *     binary search tree
 * 
 * t: a pointer to the tree
 * 
 * Returns: true if t is not a BST, false otherwise
 */ 
bool is_not_bst(inttree_t *t);